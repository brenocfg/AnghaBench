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
typedef  int u32 ;

/* Variables and functions */
 int BYPASS_AUX_OFF_M ; 
 int BYPASS_AUX_ON_M ; 
 int BYPASS_CTL1_TIME_M ; 
 int BYPASS_CTL1_VALID_M ; 
 int BYPASS_MAIN_OFF_M ; 
 int BYPASS_MAIN_ON_M ; 
#define  BYPASS_PAGE_CTL0 130 
#define  BYPASS_PAGE_CTL1 129 
#define  BYPASS_PAGE_CTL2 128 
 int BYPASS_PAGE_M ; 
 int BYPASS_STATUS_OFF_M ; 
 int BYPASS_WDTIMEOUT_M ; 
 int BYPASS_WDT_VALUE_M ; 
 int FALSE ; 
 int TRUE ; 

bool ixgbe_bypass_valid_rd_generic(u32 in_reg, u32 out_reg)
{
	u32 mask;

	/* Page must match for all control pages */
	if ((in_reg & BYPASS_PAGE_M) != (out_reg & BYPASS_PAGE_M))
		return FALSE;

	switch (in_reg & BYPASS_PAGE_M) {
	case BYPASS_PAGE_CTL0:
		/* All the following can't change since the last write
		 *  - All the event actions
		 *  - The timeout value
		 */
		mask = BYPASS_AUX_ON_M | BYPASS_MAIN_ON_M |
		       BYPASS_MAIN_OFF_M | BYPASS_AUX_OFF_M |
		       BYPASS_WDTIMEOUT_M |
		       BYPASS_WDT_VALUE_M;
		if ((out_reg & mask) != (in_reg & mask))
			return FALSE;

		/* 0x0 is never a valid value for bypass status */
		if (!(out_reg & BYPASS_STATUS_OFF_M))
			return FALSE;
		break;
	case BYPASS_PAGE_CTL1:
		/* All the following can't change since the last write
		 *  - time valid bit
		 *  - time we last sent
		 */
		mask = BYPASS_CTL1_VALID_M | BYPASS_CTL1_TIME_M;
		if ((out_reg & mask) != (in_reg & mask))
			return FALSE;
		break;
	case BYPASS_PAGE_CTL2:
		/* All we can check in this page is control number
		 * which is already done above.
		 */
		break;
	}

	/* We are as sure as we can be return TRUE */
	return TRUE;
}