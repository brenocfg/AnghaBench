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
bitcrc32(unsigned long c, void *_p, size_t s)
{
	/* This is a drop-in replacement for crc32() from zlib.
	 * Libarchive should be able to correctly generate
	 * uncompressed zip archives (including correct CRCs) even
	 * when zlib is unavailable, and this function helps us verify
	 * that.  Yes, this is very, very slow and unsuitable for
	 * production use, but it's correct, compact, and works well
	 * enough for this particular usage.  Libarchive internally
	 * uses a much more efficient implementation.  */
	const unsigned char *p = _p;
	int bitctr;

	if (p == NULL)
		return (0);

	for (; s > 0; --s) {
		c ^= *p++;
		for (bitctr = 8; bitctr > 0; --bitctr) {
			if (c & 1) c = (c >> 1);
			else	   c = (c >> 1) ^ 0xedb88320;
			c ^= 0x80000000;
		}
	}
	return (c);
}