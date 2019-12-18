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
typedef  int /*<<< orphan*/  module_t ;
struct TYPE_3__ {int /*<<< orphan*/  ipt_wrap; int /*<<< orphan*/ * ipt_func; int /*<<< orphan*/  ipt_ftype; int /*<<< orphan*/  ipt_argcnt; } ;
typedef  TYPE_1__ image_patch_table ;
typedef  int /*<<< orphan*/  funcptr ;

/* Variables and functions */
 int EINVAL ; 
#define  MOD_LOAD 130 
#define  MOD_SHUTDOWN 129 
#define  MOD_UNLOAD 128 
 int /*<<< orphan*/ * TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hal_libfini () ; 
 int /*<<< orphan*/  hal_libinit () ; 
 TYPE_1__* kernndis_functbl ; 
 int /*<<< orphan*/  ndis_devhead ; 
 int /*<<< orphan*/  ndis_libfini () ; 
 int /*<<< orphan*/  ndis_libinit () ; 
 int /*<<< orphan*/  ntoskrnl_libfini () ; 
 int /*<<< orphan*/  ntoskrnl_libinit () ; 
 int /*<<< orphan*/  usbd_libfini () ; 
 int /*<<< orphan*/  usbd_libinit () ; 
 int /*<<< orphan*/  windrv_libfini () ; 
 int /*<<< orphan*/  windrv_libinit () ; 
 int /*<<< orphan*/  windrv_unwrap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  windrv_wrap (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ndis_modevent(module_t mod, int cmd, void *arg)
{
	int			error = 0;
	image_patch_table	*patch;

	switch (cmd) {
	case MOD_LOAD:
		/* Initialize subsystems */
		hal_libinit();
		ntoskrnl_libinit();
		windrv_libinit();
		ndis_libinit();
		usbd_libinit();

		patch = kernndis_functbl;
		while (patch->ipt_func != NULL) {
			windrv_wrap((funcptr)patch->ipt_func,
			    (funcptr *)&patch->ipt_wrap,
			    patch->ipt_argcnt, patch->ipt_ftype);
			patch++;
		}

		TAILQ_INIT(&ndis_devhead);
		break;
	case MOD_SHUTDOWN:
		if (TAILQ_FIRST(&ndis_devhead) == NULL) {
			/* Shut down subsystems */
			ndis_libfini();
			usbd_libfini();
			windrv_libfini();
			ntoskrnl_libfini();
			hal_libfini();

			patch = kernndis_functbl;
			while (patch->ipt_func != NULL) {
				windrv_unwrap(patch->ipt_wrap);
				patch++;
			}
		}
		break;
	case MOD_UNLOAD:
		/* Shut down subsystems */
		ndis_libfini();
		usbd_libfini();
		windrv_libfini();
		ntoskrnl_libfini();
		hal_libfini();

		patch = kernndis_functbl;
		while (patch->ipt_func != NULL) {
			windrv_unwrap(patch->ipt_wrap);
			patch++;
		}

		break;
	default:
		error = EINVAL;
		break;
	}

	return (error);
}