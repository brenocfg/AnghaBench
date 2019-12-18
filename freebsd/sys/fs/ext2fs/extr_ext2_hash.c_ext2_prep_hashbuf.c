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
typedef  int u_int ;

/* Variables and functions */

__attribute__((used)) static void
ext2_prep_hashbuf(const char *src, int slen, uint32_t *dst, int dlen,
    int unsigned_char)
{
	uint32_t padding = slen | (slen << 8) | (slen << 16) | (slen << 24);
	uint32_t buf_val;
	const unsigned char *ubuf = (const unsigned char *)src;
	const signed char *sbuf = (const signed char *)src;
	int len, i;
	int buf_byte;

	if (slen > dlen)
		len = dlen;
	else
		len = slen;

	buf_val = padding;

	for (i = 0; i < len; i++) {
		if (unsigned_char)
			buf_byte = (u_int)ubuf[i];
		else
			buf_byte = (int)sbuf[i];

		if ((i % 4) == 0)
			buf_val = padding;

		buf_val <<= 8;
		buf_val += buf_byte;

		if ((i % 4) == 3) {
			*dst++ = buf_val;
			dlen -= sizeof(uint32_t);
			buf_val = padding;
		}
	}

	dlen -= sizeof(uint32_t);
	if (dlen >= 0)
		*dst++ = buf_val;

	dlen -= sizeof(uint32_t);
	while (dlen >= 0) {
		*dst++ = padding;
		dlen -= sizeof(uint32_t);
	}
}