#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vt_axis_t ;
struct TYPE_7__ {int /*<<< orphan*/  ta_bgcolor; } ;
typedef  TYPE_3__ teken_attr_t ;
struct vt_device {int vd_width; TYPE_2__* vd_driver; TYPE_1__* vd_curwindow; } ;
struct terminal {int /*<<< orphan*/  tm_emulator; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* vd_blank ) (struct vt_device*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* vd_drawrect ) (struct vt_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ;} ;
struct TYPE_5__ {struct terminal* vw_terminal; } ;

/* Variables and functions */
 unsigned int MIN (unsigned int,int) ; 
 unsigned int mp_ncpus ; 
 int /*<<< orphan*/  stub1 (struct vt_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct vt_device*,int /*<<< orphan*/ ) ; 
 TYPE_3__* teken_get_curattr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vt_draw_1_logo (struct vt_device*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  vt_logo_sprite_height ; 
 int vt_logo_sprite_width ; 
 int vt_splash_ncpu ; 

void
vtterm_draw_cpu_logos(struct vt_device *vd)
{
	unsigned int ncpu, i;
	vt_axis_t left;
	struct terminal *tm = vd->vd_curwindow->vw_terminal;
	const teken_attr_t *a;

	if (vt_splash_ncpu)
		ncpu = vt_splash_ncpu;
	else {
		ncpu = mp_ncpus;
		if (ncpu < 1)
			ncpu = 1;
	}

	a = teken_get_curattr(&tm->tm_emulator);
	if (vd->vd_driver->vd_drawrect)
		vd->vd_driver->vd_drawrect(vd, 0, 0, vd->vd_width,
		    vt_logo_sprite_height, 1, a->ta_bgcolor);
	/*
	 * Blank is okay because we only ever draw beasties on full screen
	 * refreshes.
	 */
	else if (vd->vd_driver->vd_blank)
		vd->vd_driver->vd_blank(vd, a->ta_bgcolor);

	ncpu = MIN(ncpu, vd->vd_width / vt_logo_sprite_width);
	for (i = 0, left = 0; i < ncpu; left += vt_logo_sprite_width, i++)
		vt_draw_1_logo(vd, 0, left);
}