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
struct vt_device {int vd_flags; } ;

/* Variables and functions */
 int VDF_INVALID ; 
 int VDF_TEXTMODE ; 
 int /*<<< orphan*/  vga_initialize (struct vt_device*,int) ; 

__attribute__((used)) static void
vga_postswitch(struct vt_device *vd)
{

	/* Reinit VGA mode, to restore view after app which change mode. */
	vga_initialize(vd, (vd->vd_flags & VDF_TEXTMODE));
	/* Ask vt(9) to update chars on visible area. */
	vd->vd_flags |= VDF_INVALID;
}