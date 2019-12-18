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
struct vt_driver {char* vd_name; } ;
struct TYPE_4__ {void* vd_softc; TYPE_1__* vd_prev_driver; struct vt_driver const* vd_driver; } ;
struct TYPE_3__ {char* vd_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  VTY_VT ; 
 TYPE_2__* main_vd ; 
 int /*<<< orphan*/  printf (char*,char*,char*) ; 
 int /*<<< orphan*/  vt_replace_backend (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vty_enabled (int /*<<< orphan*/ ) ; 

void
vt_deallocate(const struct vt_driver *drv, void *softc)
{

	if (!vty_enabled(VTY_VT))
		return;

	if (main_vd->vd_prev_driver == NULL ||
	    main_vd->vd_driver != drv ||
	    main_vd->vd_softc != softc)
		return;

	printf("VT: Switching back from \"%s\" to \"%s\".\n",
	    main_vd->vd_driver->vd_name, main_vd->vd_prev_driver->vd_name);

	vt_replace_backend(NULL, NULL);
}