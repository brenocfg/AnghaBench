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
typedef  int u32 ;
struct mii_bus {int dummy; } ;
struct ar7240sw {struct mii_bus* mii_bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR7240_REG_MAC_ADDR0 ; 
 int /*<<< orphan*/  AR7240_REG_MAC_ADDR1 ; 
 int /*<<< orphan*/  ar7240sw_reg_write (struct mii_bus*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ar7240_set_addr(struct ar7240sw *as, u8 *addr)
{
	struct mii_bus *mii = as->mii_bus;
	u32 t;

	t = (addr[4] << 8) | addr[5];
	ar7240sw_reg_write(mii, AR7240_REG_MAC_ADDR0, t);

	t = (addr[0] << 24) | (addr[1] << 16) | (addr[2] << 8) | addr[3];
	ar7240sw_reg_write(mii, AR7240_REG_MAC_ADDR1, t);

	return 0;
}