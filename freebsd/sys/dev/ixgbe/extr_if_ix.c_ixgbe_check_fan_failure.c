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
struct adapter {int /*<<< orphan*/  dev; int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 int IXGBE_EICR_GPI_SDP1_BY_MAC (int /*<<< orphan*/ *) ; 
 int IXGBE_ESDP_SDP1 ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
ixgbe_check_fan_failure(struct adapter *adapter, u32 reg, bool in_interrupt)
{
	u32 mask;

	mask = (in_interrupt) ? IXGBE_EICR_GPI_SDP1_BY_MAC(&adapter->hw) :
	    IXGBE_ESDP_SDP1;

	if (reg & mask)
		device_printf(adapter->dev, "\nCRITICAL: FAN FAILURE!! REPLACE IMMEDIATELY!!\n");
}