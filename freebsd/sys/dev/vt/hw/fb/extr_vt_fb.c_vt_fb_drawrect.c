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
struct vt_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  vt_fb_setpixel (struct vt_device*,int,int,int /*<<< orphan*/ ) ; 

void
vt_fb_drawrect(struct vt_device *vd, int x1, int y1, int x2, int y2, int fill,
    term_color_t color)
{
	int x, y;

	for (y = y1; y <= y2; y++) {
		if (fill || (y == y1) || (y == y2)) {
			for (x = x1; x <= x2; x++)
				vt_fb_setpixel(vd, x, y, color);
		} else {
			vt_fb_setpixel(vd, x1, y, color);
			vt_fb_setpixel(vd, x2, y, color);
		}
	}
}