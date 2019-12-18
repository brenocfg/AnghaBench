#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  owner; scalar_t__ nInUse; } ;
typedef  TYPE_1__ DSL_DEV_Device_t ;

/* Variables and functions */
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 

int
DSL_BSP_DriverHandleDelete (DSL_DEV_Device_t * nHandle)
{
	DSL_DEV_Device_t *pDev = (DSL_DEV_Device_t *) nHandle;
	if (pDev->nInUse)
		pDev->nInUse--;
        module_put(pDev->owner);
	return 0;
}