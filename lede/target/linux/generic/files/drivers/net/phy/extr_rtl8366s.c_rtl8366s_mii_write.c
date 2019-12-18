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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct rtl8366_smi {int dummy; } ;
struct mii_bus {struct rtl8366_smi* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  rtl8366s_read_phy_reg (struct rtl8366_smi*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int rtl8366s_write_phy_reg (struct rtl8366_smi*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rtl8366s_mii_write(struct mii_bus *bus, int addr, int reg, u16 val)
{
	struct rtl8366_smi *smi = bus->priv;
	u32 t;
	int err;

	err = rtl8366s_write_phy_reg(smi, addr, 0, reg, val);
	/* flush write */
	(void) rtl8366s_read_phy_reg(smi, addr, 0, reg, &t);

	return err;
}