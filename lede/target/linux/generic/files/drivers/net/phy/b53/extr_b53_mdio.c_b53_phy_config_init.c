#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct phy_device {TYPE_2__* attached_dev; struct b53_device* priv; } ;
struct TYPE_3__ {int /*<<< orphan*/  alias; } ;
struct b53_device {int current_page; TYPE_1__ sw_dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */

__attribute__((used)) static int b53_phy_config_init(struct phy_device *phydev)
{
	struct b53_device *dev = phydev->priv;

	/* we don't use page 0xff, so force a page set */
	dev->current_page = 0xff;
	/* force the ethX as alias */
	dev->sw_dev.alias = phydev->attached_dev->name;

	return 0;
}