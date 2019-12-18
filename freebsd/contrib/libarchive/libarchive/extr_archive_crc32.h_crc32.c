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

/* Variables and functions */

__attribute__((used)) static unsigned long
crc32(unsigned long crc, const void *_p, size_t len)
{
	unsigned long crc2, b, i;
	const unsigned char *p = _p;
	static volatile int crc_tbl_inited = 0;
	static unsigned long crc_tbl[256];

	if (!crc_tbl_inited) {
		for (b = 0; b < 256; ++b) {
			crc2 = b;
			for (i = 8; i > 0; --i) {
				if (crc2 & 1)
					crc2 = (crc2 >> 1) ^ 0xedb88320UL;
				else    
					crc2 = (crc2 >> 1);
			}
			crc_tbl[b] = crc2;
		}
		crc_tbl_inited = 1;
	}

	crc = crc ^ 0xffffffffUL;
	/* A use of this loop is about 20% - 30% faster than
	 * no use version in any optimization option of gcc.  */
	for (;len >= 8; len -= 8) {
		crc = crc_tbl[(crc ^ *p++) & 0xff] ^ (crc >> 8);
		crc = crc_tbl[(crc ^ *p++) & 0xff] ^ (crc >> 8);
		crc = crc_tbl[(crc ^ *p++) & 0xff] ^ (crc >> 8);
		crc = crc_tbl[(crc ^ *p++) & 0xff] ^ (crc >> 8);
		crc = crc_tbl[(crc ^ *p++) & 0xff] ^ (crc >> 8);
		crc = crc_tbl[(crc ^ *p++) & 0xff] ^ (crc >> 8);
		crc = crc_tbl[(crc ^ *p++) & 0xff] ^ (crc >> 8);
		crc = crc_tbl[(crc ^ *p++) & 0xff] ^ (crc >> 8);
	}
	while (len--)
		crc = crc_tbl[(crc ^ *p++) & 0xff] ^ (crc >> 8);
	return (crc ^ 0xffffffffUL);
}