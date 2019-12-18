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
struct TYPE_3__ {int /*<<< orphan*/  ipt_ftype; int /*<<< orphan*/  ipt_argcnt; int /*<<< orphan*/  ipt_wrap; int /*<<< orphan*/ * ipt_func; } ;
typedef  TYPE_1__ image_patch_table ;
typedef  int /*<<< orphan*/  funcptr ;

/* Variables and functions */
 int MTX_DEF ; 
 int MTX_RECURSE ; 
 int NDIS_MAXCPUS ; 
 int /*<<< orphan*/ * disp_lock ; 
 TYPE_1__* hal_functbl ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,char*,int) ; 
 int /*<<< orphan*/  windrv_wrap (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
hal_libinit()
{
	image_patch_table	*patch;
	int			i;

	for (i = 0; i < NDIS_MAXCPUS; i++)
		mtx_init(&disp_lock[i], "HAL preemption lock",
		    "HAL lock", MTX_RECURSE|MTX_DEF);

	patch = hal_functbl;
	while (patch->ipt_func != NULL) {
		windrv_wrap((funcptr)patch->ipt_func,
		    (funcptr *)&patch->ipt_wrap,
		    patch->ipt_argcnt, patch->ipt_ftype);
		patch++;
	}

	return (0);
}