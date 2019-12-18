#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct switch_dev {int dummy; } ;
struct b53_device {TYPE_1__* ops; } ;
struct TYPE_2__ {int (* phy_write16 ) (struct b53_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  B53_PORT_MII_PAGE (int) ; 
 int b53_write16 (struct b53_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (struct b53_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct b53_device* sw_to_b53 (struct switch_dev*) ; 

__attribute__((used)) static int b53_phy_write16(struct switch_dev *dev, int addr, u8 reg, u16 value)
{
	struct b53_device *priv = sw_to_b53(dev);

	if (priv->ops->phy_write16)
		return priv->ops->phy_write16(priv, addr, reg, value);

	return b53_write16(priv, B53_PORT_MII_PAGE(addr), reg, value);
}