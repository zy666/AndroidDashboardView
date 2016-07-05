//#include "stdafx.h"
#include "FrogSha1.h"

/********************************************/
/* Test Cases                               */
/* An array of test cases taken from the    */
/* 802.11i specification.                   */
/********************************************/

int test_case_length[] = { 9, 8, 28, 50, 50, 20, 54, 73, 54, 73 };

unsigned char test_cases[] =
{
	/* "Sample #1" */
	0x53, 0x61, 0x6d, 0x70, 0x6c, 0x65, 0x20, 0x23, 0x31,
	/* "Hi There"   */
	0x48, 0x69, 0x20, 0x54, 0x68, 0x65, 0x72, 0x65,

	/* "what do ya want for nothing?" */
	0x77, 0x68, 0x61, 0x74, 0x20, 0x64, 0x6f, 0x20, 0x79, 0x61,
	0x20, 0x77, 0x61, 0x6e, 0x74, 0x20, 0x66, 0x6f, 0x72, 0x20,
	0x6e, 0x6f, 0x74, 0x68, 0x69, 0x6e, 0x67, 0x3f,

	0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd,
	0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd,
	0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd,
	0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd,
	0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd,

	0xcd, 0xcd, 0xcd, 0xcd, 0xcd, 0xcd, 0xcd, 0xcd, 0xcd, 0xcd,
	0xcd, 0xcd, 0xcd, 0xcd, 0xcd, 0xcd, 0xcd, 0xcd, 0xcd, 0xcd,
	0xcd, 0xcd, 0xcd, 0xcd, 0xcd, 0xcd, 0xcd, 0xcd, 0xcd, 0xcd,
	0xcd, 0xcd, 0xcd, 0xcd, 0xcd, 0xcd, 0xcd, 0xcd, 0xcd, 0xcd,
	0xcd, 0xcd, 0xcd, 0xcd, 0xcd, 0xcd, 0xcd, 0xcd, 0xcd, 0xcd,

	/* "Test With Truncation" */
	0x54, 0x65, 0x73, 0x74, 0x20, 0x57, 0x69, 0x74, 0x68, 0x20, 0x54, 0x72, 0x75, 0x6e, 0x63, 0x61,
	0x74, 0x69, 0x6f, 0x6e,

	/* "Test Using Larger Than Block-Size Key - Hash Key First" */
	0x54, 0x65, 0x73, 0x74, 0x20, 0x55, 0x73, 0x69, 0x6e, 0x67, 0x20, 0x4c, 0x61, 0x72, 0x67, 0x65,
	0x72, 0x20, 0x54, 0x68, 0x61, 0x6e, 0x20, 0x42, 0x6c, 0x6f, 0x63, 0x6b, 0x2d, 0x53, 0x69, 0x7a,
	0x65, 0x20, 0x4b, 0x65, 0x79, 0x20, 0x2d, 0x20, 0x48, 0x61, 0x73, 0x68, 0x20, 0x4b, 0x65, 0x79,
	0x20, 0x46, 0x69, 0x72, 0x73, 0x74,

	/* "Test Using Larger Than Block-Size Key and Larger Than One Block-Size Data" */
	0x54, 0x65, 0x73, 0x74, 0x20, 0x55, 0x73, 0x69, 0x6e, 0x67, 0x20, 0x4c, 0x61, 0x72, 0x67, 0x65,
	0x72, 0x20, 0x54, 0x68, 0x61, 0x6e, 0x20, 0x42, 0x6c, 0x6f, 0x63, 0x6b, 0x2d, 0x53, 0x69, 0x7a,
	0x65, 0x20, 0x4b, 0x65, 0x79, 0x20, 0x61, 0x6e, 0x64, 0x20, 0x4c, 0x61, 0x72, 0x67, 0x65, 0x72,
	0x20, 0x54, 0x68, 0x61, 0x6e, 0x20, 0x4f, 0x6e, 0x65, 0x20, 0x42, 0x6c, 0x6f, 0x63, 0x6b, 0x2d,
	0x53, 0x69, 0x7a, 0x65, 0x20, 0x44, 0x61, 0x74, 0x61,


	/* "Test Using Larger Than Block-Size Key - Hash Key First" */
	0x54, 0x65, 0x73, 0x74, 0x20, 0x55, 0x73, 0x69, 0x6e, 0x67, 0x20, 0x4c, 0x61, 0x72, 0x67, 0x65,
	0x72, 0x20, 0x54, 0x68, 0x61, 0x6e, 0x20, 0x42, 0x6c, 0x6f, 0x63, 0x6b, 0x2d, 0x53, 0x69, 0x7a,
	0x65, 0x20, 0x4b, 0x65, 0x79, 0x20, 0x2d, 0x20, 0x48, 0x61, 0x73, 0x68, 0x20, 0x4b, 0x65, 0x79,
	0x20, 0x46, 0x69, 0x72, 0x73, 0x74,

	/* "Test Using Larger Than Block-Size Key and Larger Than One Block-Size Data" */
	0x54, 0x65, 0x73, 0x74, 0x20, 0x55, 0x73, 0x69, 0x6e, 0x67, 0x20, 0x4c, 0x61, 0x72, 0x67, 0x65,
	0x72, 0x20, 0x54, 0x68, 0x61, 0x6e, 0x20, 0x42, 0x6c, 0x6f, 0x63, 0x6b, 0x2d, 0x53, 0x69, 0x7a,
	0x65, 0x20, 0x4b, 0x65, 0x79, 0x20, 0x61, 0x6e, 0x64, 0x20, 0x4c, 0x61, 0x72, 0x67, 0x65, 0x72,
	0x20, 0x54, 0x68, 0x61, 0x6e, 0x20, 0x4f, 0x6e, 0x65, 0x20, 0x42, 0x6c, 0x6f, 0x63, 0x6b, 0x2d,
	0x53, 0x69, 0x7a, 0x65, 0x20, 0x44, 0x61, 0x74, 0x61
};

int key_lengths[] =
{
	64, 20, 4, 20, 25, 20, 80, 80, 80, 80
};

unsigned char keys[] =
{

	0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
	0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f,
	0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f,
	0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3a, 0x3b, 0x3c, 0x3d, 0x3e, 0x3f,


	0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b,
	0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b,
	0x0b, 0x0b, 0x0b, 0x0b,

	0x4a, 0x65, 0x66, 0x65, /* "Jefe" */

	0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
	0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,

	0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a,
	0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12, 0x13, 0x14,
	0x15, 0x16, 0x17, 0x18, 0x19,

	0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c,
	0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c,

	0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
	0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
	0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
	0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
	0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
	0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
	0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
	0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
	0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
	0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,

	0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
	0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
	0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
	0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
	0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
	0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
	0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
	0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
	0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
	0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,

	0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
	0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
	0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
	0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
	0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
	0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
	0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
	0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
	0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
	0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,

	0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
	0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
	0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
	0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
	0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
	0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
	0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
	0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
	0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
	0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa

};

/**************************/
/* Debug out              */
/**************************/

#ifdef HMAC_DEBUG
debug_out(
	unsigned char *label,
	unsigned char *data,
	int data_length
	)
{
	int i, j;
	int num_blocks;
	int block_remainder;
	num_blocks = data_length / 16;
	block_remainder = data_length % 16;

	printf("%s\n", label);

	for (i = 0; i < num_blocks; i++)
	{
		printf("\t");
		for (j = 0; j< 16; j++)
		{
			printf("%02x ", data[j + (i * 16)]);
		}
		printf("\n");
	}

	if (block_remainder > 0)
	{
		printf("\t");
		for (j = 0; j < block_remainder; j++)
		{
			printf("%02x ", data[j + (num_blocks * 16)]);
		}
		printf("\n");
	}
}
#endif

/****************************************/
/* sha1()                               */
/* Performs the NIST SHA-1 algorithm    */
/****************************************/

unsigned long int ft(
	int t,
	unsigned long int x,
	unsigned long int y,
	unsigned long int z
	)
{
	unsigned long int a, b, c;

	if (t < 20)
	{
		a = x & y;
		b = (~x) & z;
		c = a ^ b;
	}
	else if (t < 40)
	{
		c = x ^ y ^ z;
	}
	else if (t < 60)
	{
		a = x & y;
		b = a ^ (x & z);
		c = b ^ (y & z);
	}
	else if (t < 80)
	{
		c = (x ^ y) ^ z;
	}

	return c;
}

unsigned long int k(int t)
{
	unsigned long int c;

	if (t < 20)
	{
		c = 0x5a827999;
	}
	else if (t < 40)
	{
		c = 0x6ed9eba1;
	}
	else if (t < 60)
	{
		c = 0x8f1bbcdc;
	}
	else if (t < 80)
	{
		c = 0xca62c1d6;
	}

	return c;
}

unsigned long int rotr(int bits, unsigned long int a)
{
	unsigned long int c, d, e, f, g;
	c = (0x0001 << bits) - 1;
	d = ~c;

	e = (a & d) >> bits;
	f = (a & c) << (32 - bits);

	g = e | f;

	return (g & 0xffffffff);

}

unsigned long int rotl(int bits, unsigned long int a)
{
	unsigned long int c, d, e, f, g;
	c = (0x0001 << (32 - bits)) - 1;
	d = ~c;

	e = (a & c) << bits;
	f = (a & d) >> (32 - bits);

	g = e | f;

	return (g & 0xffffffff);

}


void sha1(
	unsigned char *message,
	int message_length,
	unsigned char *digest
	)
{
	int i;
	int num_blocks;
	int block_remainder;
	int padded_length;

	unsigned long int l;
	unsigned long int t;
	unsigned long int h[5];
	unsigned long int a, b, c, d, e;
	unsigned long int w[80];
	unsigned long int temp;

#ifdef SHA1_DEBUG
	int x, y;
#endif

	/* Calculate the number of 512 bit blocks */

	padded_length = message_length + 8; /* Add length for l */
	padded_length = padded_length + 1; /* Add the 0x01 bit postfix */

	l = message_length * 8;

	num_blocks = padded_length / 64;
	block_remainder = padded_length % 64;


	if (block_remainder > 0)
	{
		num_blocks++;
	}

	padded_length = padded_length + (64 - block_remainder);

	/* clear the padding field */
	for (i = message_length; i < (num_blocks * 64); i++)
	{
		message[i] = 0x00;
	}

	/* insert b1 padding bit */
	message[message_length] = 0x80;

	/* Insert l */
	message[(num_blocks * 64) - 1] = (unsigned char)(l & 0xff);
	message[(num_blocks * 64) - 2] = (unsigned char)((l >> 8) & 0xff);
	message[(num_blocks * 64) - 3] = (unsigned char)((l >> 16) & 0xff);
	message[(num_blocks * 64) - 4] = (unsigned char)((l >> 24) & 0xff);

	/* Set initial hash state */
	h[0] = 0x67452301;
	h[1] = 0xefcdab89;
	h[2] = 0x98badcfe;
	h[3] = 0x10325476;
	h[4] = 0xc3d2e1f0;

#ifdef SHA1_DEBUG
	printf("INITIAL message_length = %d\n", message_length);
	printf("INITIAL padded_length = %d\n", padded_length);
	printf("INITIAL num_blocks = %d\n", num_blocks);

	for (x = 0; x < num_blocks; x++)
	{
		printf("\t\t");
		for (y = 0; y < 16; y++)
		{
			printf("%02x ", message[y + (x * 64)]);
		}
		printf("\n");
		printf("\t\t");
		for (y = 0; y < 16; y++)
		{
			printf("%02x ", message[16 + y + (x * 64)]);
		}
		printf("\n");
		printf("\t\t");
		for (y = 0; y < 16; y++)
		{
			printf("%02x ", message[32 + y + (x * 64)]);
		}
		printf("\n");
		printf("\t\t");
		for (y = 0; y < 16; y++)
		{
			printf("%02x ", message[48 + y + (x * 64)]);
		}
		printf("\n");
	}

#endif

	for (i = 0; i < num_blocks; i++)
	{
		/* Prepare the message schedule */
		for (t = 0; t < 80; t++)
		{
			if (t < 16)
			{
				w[t] = (256 * 256 * 256) * message[(i * 64) + (t * 4)];
				w[t] += (256 * 256) * message[(i * 64) + (t * 4) + 1];
				w[t] += (256) * message[(i * 64) + (t * 4) + 2];
				w[t] += message[(i * 64) + (t * 4) + 3];
			}
			else if (t < 80)
			{
				w[t] = rotl(1, (w[t - 3] ^ w[t - 8] ^ w[t - 14] ^ w[t - 16]));
			}
		}

#ifdef SHA1_DEBUG
		printf("\tW(0) = %08lX \t W(9)  = %08lX \n", w[0], w[8]);
		printf("\tW(1) = %08lX \t W(10) = %08lX \n", w[1], w[9]);
		printf("\tW(2) = %08lX \t W(11) = %08lX \n", w[2], w[10]);
		printf("\tW(3) = %08lX \t W(12) = %08lX \n", w[3], w[11]);
		printf("\tW(4) = %08lX \t W(13) = %08lX \n", w[4], w[12]);
		printf("\tW(5) = %08lX \t W(14) = %08lX \n", w[5], w[13]);
		printf("\tW(6) = %08lX \t W(15) = %08lX \n", w[6], w[14]);
		printf("\tW(7) = %08lX \t W(16) = %08lX \n\n", w[7], w[15]);

#endif
		/* Initialize the five working variables */
		a = h[0];
		b = h[1];
		c = h[2];
		d = h[3];
		e = h[4];

		/* iterate a-e 80 times */

		for (t = 0; t < 80; t++)
		{
			temp = (rotl(5, a) + ft(t, b, c, d)) & 0xffffffff;
			temp = (temp + e) & 0xffffffff;
			temp = (temp + k(t)) & 0xffffffff;
			temp = (temp + w[t]) & 0xffffffff;
			e = d;
			d = c;
			c = rotl(30, b);
			b = a;
			a = temp;
#ifdef SHA1_DEBUG
			printf("t = %2ld\t %08lx, %08lx, %08lx, %08lx, %08lx\n", t, a, b, c, d, e);
#endif

		}

		/* compute the ith intermediate hash value */
#ifdef SHA1_DEBUG
		printf("  +   \t %08lx, %08lx, %08lx, %08lx, %08lx\n", h[0], h[1], h[2], h[3], h[4]);
#endif
		h[0] = (a + h[0]) & 0xffffffff;
		h[1] = (b + h[1]) & 0xffffffff;
		h[2] = (c + h[2]) & 0xffffffff;
		h[3] = (d + h[3]) & 0xffffffff;
		h[4] = (e + h[4]) & 0xffffffff;

#ifdef SHA1_DEBUG
		printf("  =   \t %08lx, %08lx, %08lx, %08lx, %08lx\n", h[0], h[1], h[2], h[3], h[4]);
#endif

	}

	digest[3] = (unsigned char)(h[0] & 0xff);
	digest[2] = (unsigned char)((h[0] >> 8) & 0xff);
	digest[1] = (unsigned char)((h[0] >> 16) & 0xff);
	digest[0] = (unsigned char)((h[0] >> 24) & 0xff);

	digest[7] = (unsigned char)(h[1] & 0xff);
	digest[6] = (unsigned char)((h[1] >> 8) & 0xff);
	digest[5] = (unsigned char)((h[1] >> 16) & 0xff);
	digest[4] = (unsigned char)((h[1] >> 24) & 0xff);

	digest[11] = (unsigned char)(h[2] & 0xff);
	digest[10] = (unsigned char)((h[2] >> 8) & 0xff);
	digest[9] = (unsigned char)((h[2] >> 16) & 0xff);
	digest[8] = (unsigned char)((h[2] >> 24) & 0xff);

	digest[15] = (unsigned char)(h[3] & 0xff);
	digest[14] = (unsigned char)((h[3] >> 8) & 0xff);
	digest[13] = (unsigned char)((h[3] >> 16) & 0xff);
	digest[12] = (unsigned char)((h[3] >> 24) & 0xff);

	digest[19] = (unsigned char)(h[4] & 0xff);
	digest[18] = (unsigned char)((h[4] >> 8) & 0xff);
	digest[17] = (unsigned char)((h[4] >> 16) & 0xff);
	digest[16] = (unsigned char)((h[4] >> 24) & 0xff);

}

/******************************************************/
/* hmac-sha1()                                        */
/* Performs the hmac-sha1 keyed secure hash algorithm */
/******************************************************/

void hmac_sha1(
	unsigned char *key,
	int key_length,
	unsigned char *data,
	int data_length,
	unsigned char *digest
	)

{
	int b = 64; /* blocksize */
	unsigned char ipad = 0x36;

	unsigned char opad = 0x5c;

	unsigned char k0[64];
	unsigned char k0xorIpad[64];
	unsigned char step7data[64];
	unsigned char step5data[MAX_MESSAGE_LENGTH + 128];
	unsigned char step8data[64 + 20 + 100];
	int i;

	for (i = 0; i<64; i++)
	{
		k0[i] = 0x00;
	}



	if (key_length != b)    /* Step 1 */
	{
		/* Step 2 */
		if (key_length > b)
		{
			sha1(key, key_length, digest);
			for (i = 0; i < 20; i++)
			{
				k0[i] = digest[i];
			}
		}
		else if (key_length < b)  /* Step 3 */
		{
			for (i = 0; i < key_length; i++)
			{
				k0[i] = key[i];
			}
		}
	}
	else
	{
		for (i = 0; i < b; i++)
		{
			k0[i] = key[i];
		}
	}
#ifdef HMAC_DEBUG
	debug_out("k0", k0, 64);
#endif
	/* Step 4 */
	for (i = 0; i < 64; i++)
	{
		k0xorIpad[i] = k0[i] ^ ipad;
	}
#ifdef HMAC_DEBUG
	debug_out("k0 xor ipad", k0xorIpad, 64);
#endif
	/* Step 5 */
	for (i = 0; i < 64; i++)
	{
		step5data[i] = k0xorIpad[i];
	}
	for (i = 0; i < data_length; i++)
	{
		step5data[i + 64] = data[i];
	}
#ifdef HMAC_DEBUG
	debug_out("(k0 xor ipad) || text", step5data, data_length + 64);
#endif

	/* Step 6 */
	sha1(step5data, data_length + b, digest);

#ifdef HMAC_DEBUG
	debug_out("Hash((k0 xor ipad) || text)", digest, 20);
#endif

	/* Step 7 */
	for (i = 0; i < 64; i++)
	{
		step7data[i] = k0[i] ^ opad;
	}

#ifdef HMAC_DEBUG
	debug_out("(k0 xor opad)", step7data, 64);
#endif

	/* Step 8 */
	for (i = 0; i < 64; i++)
	{
		step8data[i] = step7data[i];
	}
	for (i = 0; i < 20; i++)
	{
		step8data[i + 64] = digest[i];
	}

#ifdef HMAC_DEBUG
	debug_out("(k0 xor opad) || Hash((k0 xor ipad) || text)", step8data, 20 + 64);
#endif

	/* Step 9 */
	sha1(step8data, b + 20, digest);

#ifdef HMAC_DEBUG
	debug_out("HASH((k0 xor opad) || Hash((k0 xor ipad) || text))", digest, 20);
#endif
}

/************************************************/
/* get_testcase()                               */
/* Copies a test case from the test case data   */
/************************************************/
int get_testcase(int test_case,
	unsigned char *plaintext,
	unsigned char *key,
	int *key_length_ptr)
{
	int i;
	unsigned char *ptr;
	unsigned char *key_ptr;

	key_ptr = keys;                       /* Find and copy the key */
	for (i = 0; i < (test_case - 1); i++)
	{
		key_ptr = key_ptr + key_lengths[i];
	}

	for (i = 0; i < key_lengths[test_case - 1]; i++)
	{


		key[i] = *key_ptr++;
	}

	/* Pass back the key length */
	*key_length_ptr = key_lengths[test_case - 1];

	ptr = test_cases;
	for (i = 0; i < (test_case - 1); i++)    /* Iterate through test cases */
	{
		ptr = ptr + test_case_length[i];
	}

	for (i = 0; i < test_case_length[test_case - 1]; i++)
	{
		plaintext[i] = *ptr++;
	}

	return test_case_length[test_case - 1];
}