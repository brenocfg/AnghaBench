#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vt_axis_t ;
struct vt_device {TYPE_1__* vd_driver; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* vd_setpixel ) (struct vt_device*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct vt_device*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct vt_device*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vt_vga2bsd (unsigned char) ; 

__attribute__((used)) static void
vt_draw_2_vga16_px(struct vt_device *vd, vt_axis_t x, vt_axis_t y,
    unsigned char color)
{

	vd->vd_driver->vd_setpixel(vd, x, y, vt_vga2bsd(color >> 4));
	vd->vd_driver->vd_setpixel(vd, x + 1, y, vt_vga2bsd(color & 0xf));
}