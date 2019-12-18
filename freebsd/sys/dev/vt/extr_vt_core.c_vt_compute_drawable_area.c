#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int vt_axis_t ;
struct TYPE_5__ {int tp_col; int tp_row; } ;
struct TYPE_4__ {int tp_col; int tp_row; } ;
struct TYPE_6__ {TYPE_2__ tr_begin; TYPE_1__ tr_end; } ;
struct vt_window {TYPE_3__ vw_draw_area; struct vt_font* vw_font; struct vt_device* vw_device; } ;
struct vt_font {int vf_width; int vf_height; } ;
struct vt_device {int vd_width; int vd_height; } ;

/* Variables and functions */
 void* rounddown (int,int) ; 
 scalar_t__ vt_draw_logo_cpus ; 
 int vt_logo_sprite_height ; 

void
vt_compute_drawable_area(struct vt_window *vw)
{
	struct vt_device *vd;
	struct vt_font *vf;
	vt_axis_t height;

	vd = vw->vw_device;

	if (vw->vw_font == NULL) {
		vw->vw_draw_area.tr_begin.tp_col = 0;
		vw->vw_draw_area.tr_begin.tp_row = 0;
		if (vt_draw_logo_cpus)
			vw->vw_draw_area.tr_begin.tp_row = vt_logo_sprite_height;
		vw->vw_draw_area.tr_end.tp_col = vd->vd_width;
		vw->vw_draw_area.tr_end.tp_row = vd->vd_height;
		return;
	}

	vf = vw->vw_font;

	/*
	 * Compute the drawable area, so that the text is centered on
	 * the screen.
	 */

	height = vd->vd_height;
	if (vt_draw_logo_cpus)
		height -= vt_logo_sprite_height;
	vw->vw_draw_area.tr_begin.tp_col = (vd->vd_width % vf->vf_width) / 2;
	vw->vw_draw_area.tr_begin.tp_row = (height % vf->vf_height) / 2;
	if (vt_draw_logo_cpus)
		vw->vw_draw_area.tr_begin.tp_row += vt_logo_sprite_height;
	vw->vw_draw_area.tr_end.tp_col = vw->vw_draw_area.tr_begin.tp_col +
	    rounddown(vd->vd_width, vf->vf_width);
	vw->vw_draw_area.tr_end.tp_row = vw->vw_draw_area.tr_begin.tp_row +
	    rounddown(height, vf->vf_height);
}