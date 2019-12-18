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
typedef  long uint32_t ;
typedef  int /*<<< orphan*/  p ;

/* Variables and functions */
 long* crc_32_tab ; 

void
init_crc_table(void)
{
	/* Not copyrighted 1990 Mark Adler	*/

	uint32_t c;      /* crc shift register */
	uint32_t e;      /* polynomial exclusive-or pattern */
	int i;           /* counter for all possible eight bit values */
	int k;           /* byte being shifted into crc apparatus */

	/* terms of polynomial defining this crc (except x^32): */
	static const int p[] = {0,1,2,4,5,7,8,10,11,12,16,22,23,26};

	/* Make exclusive-or pattern from polynomial */
	e = 0;
	for (i = 0; i < sizeof(p)/sizeof(int); i++)
		e |= 1L << (31 - p[i]);

	crc_32_tab[0] = 0;

	for (i = 1; i < 256; i++) {
		c = 0;
		for (k = i | 256; k != 1; k >>= 1) {
			c = c & 1 ? (c >> 1) ^ e : c >> 1;
			if (k & 1)
				c ^= e;
		}
		crc_32_tab[i] = c;
	}
}