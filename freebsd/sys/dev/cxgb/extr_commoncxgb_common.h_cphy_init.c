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
typedef  scalar_t__ u8 ;
struct mdio_ops {int /*<<< orphan*/  write; int /*<<< orphan*/  read; } ;
struct cphy_ops {int dummy; } ;
struct cphy {unsigned int caps; char const* desc; int /*<<< orphan*/  mdio_write; int /*<<< orphan*/  mdio_read; struct cphy_ops* ops; int /*<<< orphan*/ * pinfo; int /*<<< orphan*/ * adapter; scalar_t__ addr; } ;
typedef  int /*<<< orphan*/  pinfo_t ;
typedef  int /*<<< orphan*/  adapter_t ;

/* Variables and functions */

__attribute__((used)) static inline void cphy_init(struct cphy *phy, adapter_t *adapter, pinfo_t *pinfo,
			     int phy_addr, struct cphy_ops *phy_ops,
			     const struct mdio_ops *mdio_ops, unsigned int caps,
			     const char *desc)
{
	phy->addr    = (u8)phy_addr;
	phy->caps    = caps;
	phy->adapter = adapter;
	phy->pinfo   = pinfo;
	phy->desc    = desc;
	phy->ops     = phy_ops;
	if (mdio_ops) {
		phy->mdio_read  = mdio_ops->read;
		phy->mdio_write = mdio_ops->write;
	}
}