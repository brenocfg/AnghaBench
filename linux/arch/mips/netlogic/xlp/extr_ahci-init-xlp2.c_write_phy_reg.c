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
 int /*<<< orphan*/  nlm_write_sata_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void write_phy_reg(u64 regbase, u32 addr, u32 physel, u8 data)
{
	nlm_write_sata_reg(regbase, PHY_MEM_ACCESS,
		(1u << 31) | (physel << 24) | (data << 16) | addr);
	udelay(850);
}