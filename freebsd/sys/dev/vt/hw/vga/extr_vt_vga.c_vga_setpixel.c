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
 int VT_VGA_WIDTH ; 
 int /*<<< orphan*/  vga_bitblt_put (struct vt_device*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
vga_setpixel(struct vt_device *vd, int x, int y, term_color_t color)
{

	if (vd->vd_flags & VDF_TEXTMODE)
		return;

	vga_bitblt_put(vd, (y * VT_VGA_WIDTH / 8) + (x / 8), color,
	    0x80 >> (x % 8));
}