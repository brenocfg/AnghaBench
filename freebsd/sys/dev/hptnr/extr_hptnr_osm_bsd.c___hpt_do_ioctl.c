#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int result; void* ioctl_cmnd; int /*<<< orphan*/  done; } ;
struct TYPE_11__ {scalar_t__ vbus; } ;
typedef  TYPE_1__* PVBUS_EXT ;
typedef  int /*<<< orphan*/  PVBUS ;
typedef  TYPE_2__ IOCTL_ARG ;

/* Variables and functions */
 int /*<<< orphan*/  HPT_OSM_TIMEOUT ; 
 int /*<<< orphan*/  PPAUSE ; 
 int /*<<< orphan*/  __hpt_do_tasks (TYPE_1__*) ; 
 int /*<<< orphan*/  hpt_ioctl_done ; 
 int /*<<< orphan*/  hpt_lock_vbus (TYPE_1__*) ; 
 scalar_t__ hpt_sleep (TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpt_unlock_vbus (TYPE_1__*) ; 
 int /*<<< orphan*/  ldm_ioctl (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  ldm_reset_vbus (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __hpt_do_ioctl(PVBUS_EXT vbus_ext, IOCTL_ARG *ioctl_args)
{
	ioctl_args->result = -1;
	ioctl_args->done = hpt_ioctl_done;
	ioctl_args->ioctl_cmnd = (void *)1;

	hpt_lock_vbus(vbus_ext);
	ldm_ioctl((PVBUS)vbus_ext->vbus, ioctl_args);

	while (ioctl_args->ioctl_cmnd) {
		if (hpt_sleep(vbus_ext, ioctl_args, PPAUSE, "hptctl", HPT_OSM_TIMEOUT)==0)
			break;
		ldm_reset_vbus((PVBUS)vbus_ext->vbus);
		__hpt_do_tasks(vbus_ext);
	}

	/* KdPrint(("ioctl %x result %d", ioctl_args->dwIoControlCode, ioctl_args->result)); */

	hpt_unlock_vbus(vbus_ext);
}