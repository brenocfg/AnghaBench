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
typedef  int u_int8_t ;
typedef  int u_int ;

/* Variables and functions */

__attribute__((used)) static void
ubsec_kshift_l(
	u_int shiftbits,
	u_int8_t *src, u_int srcbits,
	u_int8_t *dst, u_int dstbits)
{
	int slen, dlen, i, n;

	slen = (srcbits + 7) / 8;
	dlen = (dstbits + 7) / 8;

	n = shiftbits / 8;
	for (i = 0; i < slen; i++)
		dst[i] = src[i + n];
	for (i = 0; i < dlen - slen; i++)
		dst[slen + i] = 0;

	n = shiftbits % 8;
	if (n != 0) {
		for (i = 0; i < (dlen - 1); i++)
			dst[i] = (dst[i] >> n) | (dst[i + 1] << (8 - n));
		dst[dlen - 1] = dst[dlen - 1] >> n;
	}
}