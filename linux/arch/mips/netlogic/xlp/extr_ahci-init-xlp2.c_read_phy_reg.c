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
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  PHY_MEM_ACCESS ; 
 int nlm_read_sata_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlm_write_sata_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static u8 read_phy_reg(u64 regbase, u32 addr, u32 physel)
{
	u32 val;

	nlm_write_sata_reg(regbase, PHY_MEM_ACCESS,
		(0 << 31) | (physel << 24) | (0 << 16) | addr);
	udelay(850);
	val = nlm_read_sata_reg(regbase, PHY_MEM_ACCESS);
	return (val >> 16) & 0xff;
}