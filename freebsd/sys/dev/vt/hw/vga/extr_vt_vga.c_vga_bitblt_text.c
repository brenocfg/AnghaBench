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
typedef  int /*<<< orphan*/  term_rect_t ;
struct vt_window {int dummy; } ;
struct vt_device {int vd_flags; } ;

/* Variables and functions */
 int VDF_TEXTMODE ; 
 int /*<<< orphan*/  vga_bitblt_text_gfxmode (struct vt_device*,struct vt_window const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  vga_bitblt_text_txtmode (struct vt_device*,struct vt_window const*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void
vga_bitblt_text(struct vt_device *vd, const struct vt_window *vw,
    const term_rect_t *area)
{

	if (!(vd->vd_flags & VDF_TEXTMODE)) {
		vga_bitblt_text_gfxmode(vd, vw, area);
	} else {
		vga_bitblt_text_txtmode(vd, vw, area);
	}
}