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
typedef  int uint8_t ;
typedef  int uint32_t ;

/* Variables and functions */

__attribute__((used)) static void
krb5_rotate_right_13(uint8_t *out, uint8_t *in, size_t numlen)
{
	uint32_t carry;
	size_t i;

	/*
	 * Special case when numlen == 1. A rotate right 13 of a
	 * single byte number changes to a rotate right 5.
	 */
	if (numlen == 1) {
		carry = in[0] >> 5;
		out[0] = (in[0] << 3) | carry;
		return;
	}

	carry = ((in[numlen - 2] & 31) << 8) | in[numlen - 1];
	for (i = 2; i < numlen; i++) {
		out[i] = ((in[i - 2] & 31) << 3) | (in[i - 1] >> 5);
	}
	out[1] = ((carry & 31) << 3) | (in[0] >> 5);
	out[0] = carry >> 5;
}