#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint32_t ;

/* Variables and functions */
 int SIZE_MAX ; 
 char* malloc (size_t) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static char *
b64enc(const char *ptext)
{
	static const char base64[] =
	    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
	    "abcdefghijklmnopqrstuvwxyz"
	    "0123456789+/";
	const char *pt;
	char *ctext, *pc;
	size_t ptlen, ctlen;
	uint32_t t;
	unsigned int j;

	/*
	 * Encoded length is 4 characters per 3-byte block or partial
	 * block of plaintext, plus one byte for the terminating NUL
	 */
	ptlen = strlen(ptext);
	if (ptlen > ((SIZE_MAX - 1) / 4) * 3 - 2)
		return NULL;	/* Possible integer overflow */
	ctlen = 4 * ((ptlen + 2) / 3) + 1;
	if ((ctext = malloc(ctlen)) == NULL)
		return NULL;
	ctext[ctlen - 1] = 0;

	/*
	 * Scan through ptext, reading up to 3 bytes from ptext and
	 * writing 4 bytes to ctext, until we run out of input.
	 */
	for (pt = ptext, pc = ctext; ptlen; ptlen -= 3, pc += 4) {
		/* Read 3 bytes */
		for (t = j = 0; j < 3; j++) {
			t <<= 8;
			if (j < ptlen)
				t += *pt++;
		}

		/* Write 4 bytes */
		for (j = 0; j < 4; j++) {
			if (j <= ptlen + 1)
				pc[j] = base64[(t >> 18) & 0x3f];
			else
				pc[j] = '=';
			t <<= 6;
		}

		/* If we're done, exit the loop */
		if (ptlen <= 3)
			break;
	}

	return (ctext);
}