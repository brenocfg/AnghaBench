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
struct TYPE_2__ {scalar_t__ id; } ;
struct expansion_card {TYPE_1__ cid; } ;
struct ecard_driver {scalar_t__ id; scalar_t__ id_table; } ;
struct device_driver {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct expansion_card* ECARD_DEV (struct device*) ; 
 struct ecard_driver* ECARD_DRV (struct device_driver*) ; 
 int /*<<< orphan*/ * ecard_match_device (scalar_t__,struct expansion_card*) ; 

__attribute__((used)) static int ecard_match(struct device *_dev, struct device_driver *_drv)
{
	struct expansion_card *ec = ECARD_DEV(_dev);
	struct ecard_driver *drv = ECARD_DRV(_drv);
	int ret;

	if (drv->id_table) {
		ret = ecard_match_device(drv->id_table, ec) != NULL;
	} else {
		ret = ec->cid.id == drv->id;
	}

	return ret;
}