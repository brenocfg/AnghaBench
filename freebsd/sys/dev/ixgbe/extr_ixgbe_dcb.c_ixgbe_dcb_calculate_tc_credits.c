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
typedef  int u8 ;
typedef  int u16 ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int IXGBE_DCB_CREDIT_QUANTUM ; 
 int IXGBE_DCB_MAX_CREDIT ; 
 int /*<<< orphan*/  IXGBE_DCB_MAX_CREDIT_REFILL ; 
 int IXGBE_DCB_MAX_TRAFFIC_CLASS ; 
 int min (int,int /*<<< orphan*/ ) ; 

s32 ixgbe_dcb_calculate_tc_credits(u8 *bw, u16 *refill, u16 *max,
				   int max_frame_size)
{
	int min_percent = 100;
	int min_credit, multiplier;
	int i;

	min_credit = ((max_frame_size / 2) + IXGBE_DCB_CREDIT_QUANTUM - 1) /
			IXGBE_DCB_CREDIT_QUANTUM;

	for (i = 0; i < IXGBE_DCB_MAX_TRAFFIC_CLASS; i++) {
		if (bw[i] < min_percent && bw[i])
			min_percent = bw[i];
	}

	multiplier = (min_credit / min_percent) + 1;

	/* Find out the hw credits for each TC */
	for (i = 0; i < IXGBE_DCB_MAX_TRAFFIC_CLASS; i++) {
		int val = min(bw[i] * multiplier, IXGBE_DCB_MAX_CREDIT_REFILL);

		if (val < min_credit)
			val = min_credit;
		refill[i] = (u16)val;

		max[i] = bw[i] ? (bw[i]*IXGBE_DCB_MAX_CREDIT)/100 : min_credit;
	}

	return 0;
}