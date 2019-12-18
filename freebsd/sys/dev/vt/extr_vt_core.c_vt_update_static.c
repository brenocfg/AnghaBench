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
struct TYPE_4__ {int vd_flags; int vd_width; int vd_height; int /*<<< orphan*/  vd_winswitch; int /*<<< orphan*/  vd_lock; TYPE_1__* vd_driver; } ;
struct TYPE_3__ {char* vd_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTX_DEF ; 
 int VDF_TEXTMODE ; 
 int /*<<< orphan*/  VTY_VT ; 
 int /*<<< orphan*/  cv_init (int /*<<< orphan*/ *,char*) ; 
 TYPE_2__* main_vd ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  vty_enabled (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vt_update_static(void *dummy)
{

	if (!vty_enabled(VTY_VT))
		return;
	if (main_vd->vd_driver != NULL)
		printf("VT(%s): %s %ux%u\n", main_vd->vd_driver->vd_name,
		    (main_vd->vd_flags & VDF_TEXTMODE) ? "text" : "resolution",
		    main_vd->vd_width, main_vd->vd_height);
	else
		printf("VT: init without driver.\n");

	mtx_init(&main_vd->vd_lock, "vtdev", NULL, MTX_DEF);
	cv_init(&main_vd->vd_winswitch, "vtwswt");
}