#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct winsize {int /*<<< orphan*/  ws_col; int /*<<< orphan*/  ws_row; int /*<<< orphan*/  ws_xpixel; int /*<<< orphan*/  ws_ypixel; } ;
struct vt_font {int /*<<< orphan*/  vf_width; int /*<<< orphan*/  vf_height; } ;
struct vt_device {int /*<<< orphan*/  vd_width; int /*<<< orphan*/  vd_height; } ;

/* Variables and functions */
 scalar_t__ vt_draw_logo_cpus ; 
 scalar_t__ vt_logo_sprite_height ; 

void
vt_winsize(struct vt_device *vd, struct vt_font *vf, struct winsize *size)
{

	size->ws_ypixel = vd->vd_height;
	if (vt_draw_logo_cpus)
		size->ws_ypixel -= vt_logo_sprite_height;
	size->ws_row = size->ws_ypixel;
	size->ws_col = size->ws_xpixel = vd->vd_width;
	if (vf != NULL) {
		size->ws_row /= vf->vf_height;
		size->ws_col /= vf->vf_width;
	}
}