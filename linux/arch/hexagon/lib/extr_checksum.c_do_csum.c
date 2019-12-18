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
typedef  int u64 ;

/* Variables and functions */
 int HEXAGON_P_vrmpyh_PP (int,scalar_t__) ; 
 int HEXAGON_P_vrmpyhacc_PP (int,int,scalar_t__) ; 
 int HEXAGON_R_cl0_R (int) ; 
 scalar_t__ VR_CARRY (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int VR_NEGATE (int,int,int,int) ; 
 scalar_t__ VR_SELECT (int,int,int,int) ; 

unsigned int do_csum(const void *voidptr, int len)
{
	u64 sum0, sum1, x0, x1, *ptr8_o, *ptr8_e, *ptr8;
	int i, start, mid, end, mask;
	const char *ptr = voidptr;
	unsigned short *ptr2;
	unsigned int *ptr4;

	if (len <= 0)
		return 0;

	start = 0xF & (16-(((int) ptr) & 0xF)) ;
	mask  = 0x7fffffffUL >> HEXAGON_R_cl0_R(len);
	start = start & mask ;

	mid = len - start;
	end = mid & 0xF;
	mid = mid>>4;
	sum0 = mid << 18;
	sum1 = 0;

	if (start & 1)
		sum0 += (u64) (ptr[0] << 8);
	ptr2 = (unsigned short *) &ptr[start & 1];
	if (start & 2)
		sum1 += (u64) ptr2[0];
	ptr4 = (unsigned int *) &ptr[start & 3];
	if (start & 4) {
		sum0 = HEXAGON_P_vrmpyhacc_PP(sum0,
			VR_NEGATE(0, 0, 1, 1)^((u64)ptr4[0]),
			VR_SELECT(0, 0, 1, 1));
		sum0 += VR_SELECT(0, 0, 1, 0);
	}
	ptr8 = (u64 *) &ptr[start & 7];
	if (start & 8) {
		sum1 = HEXAGON_P_vrmpyhacc_PP(sum1,
			VR_NEGATE(1, 1, 1, 1)^(ptr8[0]),
			VR_SELECT(1, 1, 1, 1));
		sum1 += VR_CARRY(0, 0, 1, 0);
	}
	ptr8_o = (u64 *) (ptr + start);
	ptr8_e = (u64 *) (ptr + start + 8);

	if (mid) {
		x0 = *ptr8_e; ptr8_e += 2;
		x1 = *ptr8_o; ptr8_o += 2;
		if (mid > 1)
			for (i = 0; i < mid-1; i++) {
				sum0 = HEXAGON_P_vrmpyhacc_PP(sum0,
					x0^VR_NEGATE(1, 1, 1, 1),
					VR_SELECT(1, 1, 1, 1));
				sum1 = HEXAGON_P_vrmpyhacc_PP(sum1,
					x1^VR_NEGATE(1, 1, 1, 1),
					VR_SELECT(1, 1, 1, 1));
				x0 = *ptr8_e; ptr8_e += 2;
				x1 = *ptr8_o; ptr8_o += 2;
			}
		sum0 = HEXAGON_P_vrmpyhacc_PP(sum0, x0^VR_NEGATE(1, 1, 1, 1),
			VR_SELECT(1, 1, 1, 1));
		sum1 = HEXAGON_P_vrmpyhacc_PP(sum1, x1^VR_NEGATE(1, 1, 1, 1),
			VR_SELECT(1, 1, 1, 1));
	}

	ptr4 = (unsigned int *) &ptr[start + (mid * 16) + (end & 8)];
	if (end & 4) {
		sum1 = HEXAGON_P_vrmpyhacc_PP(sum1,
			VR_NEGATE(0, 0, 1, 1)^((u64)ptr4[0]),
			VR_SELECT(0, 0, 1, 1));
		sum1 += VR_SELECT(0, 0, 1, 0);
	}
	ptr2 = (unsigned short *) &ptr[start + (mid * 16) + (end & 12)];
	if (end & 2)
		sum0 += (u64) ptr2[0];

	if (end & 1)
		sum1 += (u64) ptr[start + (mid * 16) + (end & 14)];

	ptr8 = (u64 *) &ptr[start + (mid * 16)];
	if (end & 8) {
		sum0 = HEXAGON_P_vrmpyhacc_PP(sum0,
			VR_NEGATE(1, 1, 1, 1)^(ptr8[0]),
			VR_SELECT(1, 1, 1, 1));
		sum0 += VR_CARRY(0, 0, 1, 0);
	}
	sum0 = HEXAGON_P_vrmpyh_PP((sum0+sum1)^VR_NEGATE(0, 0, 0, 1),
		VR_SELECT(0, 0, 1, 1));
	sum0 += VR_NEGATE(0, 0, 0, 1);
	sum0 = HEXAGON_P_vrmpyh_PP(sum0, VR_SELECT(0, 0, 1, 1));

	if (start & 1)
		sum0 = (sum0 << 8) | (0xFF & (sum0 >> 8));

	return 0xFFFF & sum0;
}