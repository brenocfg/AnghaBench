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
typedef  int /*<<< orphan*/  term_color_t ;
struct vt_device {int vd_flags; } ;

/* Variables and functions */
 int VDF_TEXTMODE ; 
 int /*<<< orphan*/  vga_setpixel (struct vt_device*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vga_drawrect(struct vt_device *vd, int x1, int y1, int x2, int y2, int fill,
    term_color_t color)
{
	int x, y;

	if (vd->vd_flags & VDF_TEXTMODE)
		return;

	for (y = y1; y <= y2; y++) {
		if (fill || (y == y1) || (y == y2)) {
			for (x = x1; x <= x2; x++)
				vga_setpixel(vd, x, y, color);
		} else {
			vga_setpixel(vd, x1, y, color);
			vga_setpixel(vd, x2, y, color);
		}
	}
}