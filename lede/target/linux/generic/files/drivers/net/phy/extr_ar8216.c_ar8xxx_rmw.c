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
typedef  int u16 ;
struct mii_bus {int /*<<< orphan*/  mdio_lock; int /*<<< orphan*/  (* write ) (struct mii_bus*,int,int /*<<< orphan*/ ,int) ;} ;
struct ar8xxx_priv {struct mii_bus* mii_bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  ar8xxx_mii_read32 (struct ar8xxx_priv*,int,int) ; 
 int /*<<< orphan*/  ar8xxx_mii_write32 (struct ar8xxx_priv*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  split_addr (int /*<<< orphan*/ ,int*,int*,int*) ; 
 int /*<<< orphan*/  stub1 (struct mii_bus*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wait_for_page_switch () ; 

u32
ar8xxx_rmw(struct ar8xxx_priv *priv, int reg, u32 mask, u32 val)
{
	struct mii_bus *bus = priv->mii_bus;
	u16 r1, r2, page;
	u32 ret;

	split_addr((u32) reg, &r1, &r2, &page);

	mutex_lock(&bus->mdio_lock);

	bus->write(bus, 0x18, 0, page);
	wait_for_page_switch();

	ret = ar8xxx_mii_read32(priv, 0x10 | r2, r1);
	ret &= ~mask;
	ret |= val;
	ar8xxx_mii_write32(priv, 0x10 | r2, r1, ret);

	mutex_unlock(&bus->mdio_lock);

	return ret;
}