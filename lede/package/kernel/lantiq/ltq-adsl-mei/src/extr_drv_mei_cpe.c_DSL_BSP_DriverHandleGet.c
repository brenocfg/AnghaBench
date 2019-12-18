#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  nInUse; int /*<<< orphan*/  owner; } ;
typedef  TYPE_1__ DSL_DEV_Device_t ;

/* Variables and functions */
 int BSP_MAX_DEVICES ; 
 TYPE_1__* dsl_devices ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

DSL_DEV_Device_t *
DSL_BSP_DriverHandleGet (int maj, int num)
{
	DSL_DEV_Device_t *pDev;

	if (num > BSP_MAX_DEVICES)
		return NULL;

	pDev = &dsl_devices[num];
	if (!try_module_get(pDev->owner))
		return NULL;

	pDev->nInUse++;
	return pDev;
}