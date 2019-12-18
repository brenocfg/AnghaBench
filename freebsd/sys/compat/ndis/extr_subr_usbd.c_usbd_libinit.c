#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int ipt_argcnt; int /*<<< orphan*/  ipt_ftype; int /*<<< orphan*/  ipt_wrap; int /*<<< orphan*/ * ipt_func; } ;
typedef  TYPE_1__ image_patch_table ;
typedef  int /*<<< orphan*/  funcptr ;
typedef  void* driver_dispatch ;
struct TYPE_6__ {void** dro_dispatch; } ;

/* Variables and functions */
 size_t IRP_MJ_DEVICE_CONTROL ; 
 size_t IRP_MJ_INTERNAL_DEVICE_CONTROL ; 
 int IRP_MJ_MAXIMUM_FUNCTION ; 
 size_t IRP_MJ_PNP ; 
 size_t IRP_MJ_POWER ; 
 int /*<<< orphan*/  WINDRV_WRAP_STDCALL ; 
 TYPE_2__ usbd_driver ; 
 TYPE_1__* usbd_functbl ; 
 scalar_t__ usbd_iodispatch ; 
 scalar_t__ usbd_iodispatch_wrap ; 
 scalar_t__ usbd_ioinvalid ; 
 scalar_t__ usbd_ioinvalid_wrap ; 
 scalar_t__ usbd_irpcancel ; 
 int /*<<< orphan*/  usbd_irpcancel_wrap ; 
 scalar_t__ usbd_pnp ; 
 scalar_t__ usbd_pnp_wrap ; 
 scalar_t__ usbd_power ; 
 scalar_t__ usbd_power_wrap ; 
 scalar_t__ usbd_task ; 
 int /*<<< orphan*/  usbd_task_wrap ; 
 scalar_t__ usbd_xfertask ; 
 int /*<<< orphan*/  usbd_xfertask_wrap ; 
 int /*<<< orphan*/  windrv_bus_attach (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  windrv_wrap (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

int
usbd_libinit(void)
{
	image_patch_table	*patch;
	int i;

	patch = usbd_functbl;
	while (patch->ipt_func != NULL) {
		windrv_wrap((funcptr)patch->ipt_func,
		    (funcptr *)&patch->ipt_wrap,
		    patch->ipt_argcnt, patch->ipt_ftype);
		patch++;
	}

	windrv_wrap((funcptr)usbd_ioinvalid,
	    (funcptr *)&usbd_ioinvalid_wrap, 2, WINDRV_WRAP_STDCALL);
	windrv_wrap((funcptr)usbd_iodispatch,
	    (funcptr *)&usbd_iodispatch_wrap, 2, WINDRV_WRAP_STDCALL);
	windrv_wrap((funcptr)usbd_pnp,
	    (funcptr *)&usbd_pnp_wrap, 2, WINDRV_WRAP_STDCALL);
	windrv_wrap((funcptr)usbd_power,
	    (funcptr *)&usbd_power_wrap, 2, WINDRV_WRAP_STDCALL);
	windrv_wrap((funcptr)usbd_irpcancel,
	    (funcptr *)&usbd_irpcancel_wrap, 2, WINDRV_WRAP_STDCALL);
	windrv_wrap((funcptr)usbd_task,
	    (funcptr *)&usbd_task_wrap, 2, WINDRV_WRAP_STDCALL);
	windrv_wrap((funcptr)usbd_xfertask,
	    (funcptr *)&usbd_xfertask_wrap, 2, WINDRV_WRAP_STDCALL);

	/* Create a fake USB driver instance. */

	windrv_bus_attach(&usbd_driver, "USB Bus");

	/* Set up our dipatch routine. */
	for (i = 0; i <= IRP_MJ_MAXIMUM_FUNCTION; i++)
		usbd_driver.dro_dispatch[i] =
			(driver_dispatch)usbd_ioinvalid_wrap;

	usbd_driver.dro_dispatch[IRP_MJ_INTERNAL_DEVICE_CONTROL] =
	    (driver_dispatch)usbd_iodispatch_wrap;
	usbd_driver.dro_dispatch[IRP_MJ_DEVICE_CONTROL] =
	    (driver_dispatch)usbd_iodispatch_wrap;
	usbd_driver.dro_dispatch[IRP_MJ_POWER] =
	    (driver_dispatch)usbd_power_wrap;
	usbd_driver.dro_dispatch[IRP_MJ_PNP] =
	    (driver_dispatch)usbd_pnp_wrap;

	return (0);
}