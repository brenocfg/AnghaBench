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
typedef  scalar_t__ uint8_t ;
typedef  int uint32_t ;

/* Variables and functions */

__attribute__((used)) static int
xlp_rsa_inp2hwformat(uint8_t *src, uint8_t *dst, uint32_t paramsize,
    uint8_t result)
{
	uint32_t pdwords, pbytes;
	int i, j, k;

	pdwords = paramsize / 8;
	pbytes = paramsize % 8;

	for (i = 0, k = 0; i < pdwords; i++) {
		/* copy dwords of inp/hw to hw/out format */
		for (j = 7; j >= 0; j--, k++)
			dst[i * 8 + j] = src[k];
	}
	if (pbytes) {
		if (result == 0) {
			/* copy rem bytes of input data to hw format */
			for (j = 7; k < paramsize; j--, k++)
				dst[i * 8 + j] = src[k];
		} else {
			/* copy rem bytes of hw data to exp output format */
			for (j = 7; k < paramsize; j--, k++)
				dst[k] = src[i * 8 + j];
		}
	}

	return (0);
}