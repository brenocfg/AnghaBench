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
typedef  int UINT ;

/* Variables and functions */
 scalar_t__ C_DDR_REG_PHY2 ; 

__attribute__((used)) static void ddr_phy_poll_until_locked(void)
{
	volatile UINT reg_tmp = 0;
	volatile UINT locked = 0;

	//Extra read to put in delay before starting to poll...
	reg_tmp = *(volatile UINT *) C_DDR_REG_PHY2;      // read

	//POLL C_DDR_PHY2_REG register until clock and flock
	//!!! Ideally have a timeout on this.
	while (locked == 0) {
		reg_tmp = *(volatile UINT *) C_DDR_REG_PHY2;      // read

		//locked when bits 30 and 31 are set
		if (reg_tmp & 0xC0000000) {
			locked = 1;
		}
	}
}