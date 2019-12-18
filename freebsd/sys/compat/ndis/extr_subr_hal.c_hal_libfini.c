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
struct TYPE_3__ {int /*<<< orphan*/  ipt_wrap; int /*<<< orphan*/ * ipt_func; } ;
typedef  TYPE_1__ image_patch_table ;

/* Variables and functions */
 int NDIS_MAXCPUS ; 
 int /*<<< orphan*/ * disp_lock ; 
 TYPE_1__* hal_functbl ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  windrv_unwrap (int /*<<< orphan*/ ) ; 

int
hal_libfini()
{
	image_patch_table	*patch;
	int			i;

	for (i = 0; i < NDIS_MAXCPUS; i++)
		mtx_destroy(&disp_lock[i]);

	patch = hal_functbl;
	while (patch->ipt_func != NULL) {
		windrv_unwrap(patch->ipt_wrap);
		patch++;
	}

	return (0);
}