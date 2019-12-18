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
struct omap_device {struct omap_device* hwmods; TYPE_2__* pdev; } ;
struct TYPE_3__ {int /*<<< orphan*/ * od; } ;
struct TYPE_4__ {TYPE_1__ archdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct omap_device*) ; 

void omap_device_delete(struct omap_device *od)
{
	if (!od)
		return;

	od->pdev->archdata.od = NULL;
	kfree(od->hwmods);
	kfree(od);
}