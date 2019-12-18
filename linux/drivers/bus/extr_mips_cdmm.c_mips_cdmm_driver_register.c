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
struct TYPE_2__ {int /*<<< orphan*/  shutdown; int /*<<< orphan*/  remove; int /*<<< orphan*/  probe; int /*<<< orphan*/ * bus; } ;
struct mips_cdmm_driver {TYPE_1__ drv; scalar_t__ shutdown; scalar_t__ remove; scalar_t__ probe; } ;

/* Variables and functions */
 int driver_register (TYPE_1__*) ; 
 int /*<<< orphan*/  mips_cdmm_bustype ; 
 int /*<<< orphan*/  mips_cdmm_probe ; 
 int /*<<< orphan*/  mips_cdmm_remove ; 
 int /*<<< orphan*/  mips_cdmm_shutdown ; 

int mips_cdmm_driver_register(struct mips_cdmm_driver *drv)
{
	drv->drv.bus = &mips_cdmm_bustype;

	if (drv->probe)
		drv->drv.probe = mips_cdmm_probe;
	if (drv->remove)
		drv->drv.remove = mips_cdmm_remove;
	if (drv->shutdown)
		drv->drv.shutdown = mips_cdmm_shutdown;

	return driver_register(&drv->drv);
}