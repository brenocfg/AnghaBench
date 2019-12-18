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
typedef  size_t u8 ;
struct ixgbe_dcb_tc_config {scalar_t__ pfc; } ;
struct ixgbe_dcb_config {struct ixgbe_dcb_tc_config* tc_config; } ;

/* Variables and functions */
 int IXGBE_DCB_MAX_USER_PRIORITY ; 
 scalar_t__ ixgbe_dcb_pfc_disabled ; 

void ixgbe_dcb_unpack_pfc_cee(struct ixgbe_dcb_config *cfg, u8 *map, u8 *pfc_up)
{
	struct ixgbe_dcb_tc_config *tc_config = &cfg->tc_config[0];
	int up;

	/*
	 * If the TC for this user priority has PFC enabled then set the
	 * matching bit in 'pfc_up' to reflect that PFC is enabled.
	 */
	for (*pfc_up = 0, up = 0; up < IXGBE_DCB_MAX_USER_PRIORITY; up++) {
		if (tc_config[map[up]].pfc != ixgbe_dcb_pfc_disabled)
			*pfc_up |= 1 << up;
	}
}