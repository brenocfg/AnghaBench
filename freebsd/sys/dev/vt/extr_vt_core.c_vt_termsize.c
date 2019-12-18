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
struct TYPE_3__ {int /*<<< orphan*/  tp_col; int /*<<< orphan*/  tp_row; } ;
typedef  TYPE_1__ term_pos_t ;
struct vt_font {int /*<<< orphan*/  vf_width; int /*<<< orphan*/  vf_height; } ;
struct vt_device {int /*<<< orphan*/  vd_width; int /*<<< orphan*/  vd_height; } ;

/* Variables and functions */
 scalar_t__ vt_draw_logo_cpus ; 
 scalar_t__ vt_logo_sprite_height ; 

void
vt_termsize(struct vt_device *vd, struct vt_font *vf, term_pos_t *size)
{

	size->tp_row = vd->vd_height;
	if (vt_draw_logo_cpus)
		size->tp_row -= vt_logo_sprite_height;
	size->tp_col = vd->vd_width;
	if (vf != NULL) {
		size->tp_row /= vf->vf_height;
		size->tp_col /= vf->vf_width;
	}
}