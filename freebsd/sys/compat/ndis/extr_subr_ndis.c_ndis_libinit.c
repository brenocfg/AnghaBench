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
 int /*<<< orphan*/  ndis_filepath ; 
 TYPE_1__* ndis_functbl ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  windrv_wrap (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
ndis_libinit()
{
	image_patch_table	*patch;

	strcpy(ndis_filepath, "/compat/ndis");

	patch = ndis_functbl;
	while (patch->ipt_func != NULL) {
		windrv_wrap((funcptr)patch->ipt_func,
		    (funcptr *)&patch->ipt_wrap,
		    patch->ipt_argcnt, patch->ipt_ftype);
		patch++;
	}

	return (0);
}