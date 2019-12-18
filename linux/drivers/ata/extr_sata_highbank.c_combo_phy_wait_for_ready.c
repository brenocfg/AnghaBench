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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 int CR_BUSY ; 
 int /*<<< orphan*/  SERDES_CR_CTL ; 
 int __combo_phy_reg_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void combo_phy_wait_for_ready(u8 sata_port)
{
	while (__combo_phy_reg_read(sata_port, SERDES_CR_CTL) & CR_BUSY)
		udelay(5);
}