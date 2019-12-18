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
typedef  int u32 ;

/* Variables and functions */
 int CR_START ; 
 int CR_WR_RDN ; 
 int /*<<< orphan*/  SERDES_CR_ADDR ; 
 int /*<<< orphan*/  SERDES_CR_CTL ; 
 int /*<<< orphan*/  SERDES_CR_DATA ; 
 int /*<<< orphan*/  __combo_phy_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  combo_phy_wait_for_ready (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void combo_phy_write(u8 sata_port, u32 addr, u32 data)
{
	combo_phy_wait_for_ready(sata_port);
	__combo_phy_reg_write(sata_port, SERDES_CR_ADDR, addr);
	__combo_phy_reg_write(sata_port, SERDES_CR_DATA, data);
	__combo_phy_reg_write(sata_port, SERDES_CR_CTL, CR_WR_RDN | CR_START);
}