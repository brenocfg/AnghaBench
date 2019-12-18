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
typedef  int /*<<< orphan*/  u16 ;
struct switch_dev {int dummy; } ;
struct rtl_priv {struct mii_bus* bus; } ;
struct mii_bus {int /*<<< orphan*/  (* read ) (struct mii_bus*,unsigned int,unsigned int) ;int /*<<< orphan*/  (* write ) (struct mii_bus*,unsigned int,unsigned int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  rtl_set_page (struct rtl_priv*,unsigned int) ; 
 int /*<<< orphan*/  stub1 (struct mii_bus*,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct mii_bus*,unsigned int,unsigned int) ; 
 struct rtl_priv* to_rtl (struct switch_dev*) ; 

__attribute__((used)) static inline int
rtl_w16(struct switch_dev *dev, unsigned int page, unsigned int phy, unsigned int reg, u16 val)
{
	struct rtl_priv *priv = to_rtl(dev);
	struct mii_bus *bus = priv->bus;

	rtl_set_page(priv, page);
	bus->write(bus, phy, reg, val);
	bus->read(bus, phy, reg); /* flush */
	return 0;
}