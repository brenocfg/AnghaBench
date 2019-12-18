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
struct vt_device {struct fb_info* vd_softc; } ;
struct fb_info {int /*<<< orphan*/  fb_priv; int /*<<< orphan*/  (* enter ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

void
vt_fb_postswitch(struct vt_device *vd)
{
	struct fb_info *info;

	info = vd->vd_softc;

	if (info->enter != NULL)
		info->enter(info->fb_priv);
}