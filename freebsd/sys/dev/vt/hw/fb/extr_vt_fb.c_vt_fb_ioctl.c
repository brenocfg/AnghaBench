#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
typedef  TYPE_2__ video_display_start_t ;
typedef  int u_long ;
typedef  int /*<<< orphan*/  u_int ;
struct vt_device {TYPE_1__* vd_driver; struct fb_info* vd_softc; } ;
struct thread {int dummy; } ;
struct fbtype {int dummy; } ;
struct fb_info {int /*<<< orphan*/  fb_stride; } ;
typedef  scalar_t__ caddr_t ;
struct TYPE_3__ {int /*<<< orphan*/  (* vd_blank ) (struct vt_device*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int ENODEV ; 
 int ENOIOCTL ; 
#define  FBIOGTYPE 132 
#define  FBIO_BLANK 131 
#define  FBIO_GETDISPSTART 130 
#define  FBIO_GETLINEWIDTH 129 
#define  FBIO_GETWINORG 128 
 int /*<<< orphan*/  TC_BLACK ; 
 int /*<<< orphan*/  bcopy (struct fb_info*,struct fbtype*,int) ; 
 int /*<<< orphan*/  stub1 (struct vt_device*,int /*<<< orphan*/ ) ; 

int
vt_fb_ioctl(struct vt_device *vd, u_long cmd, caddr_t data, struct thread *td)
{
	struct fb_info *info;
	int error = 0;

	info = vd->vd_softc;

	switch (cmd) {
	case FBIOGTYPE:
		bcopy(info, (struct fbtype *)data, sizeof(struct fbtype));
		break;

	case FBIO_GETWINORG:	/* get frame buffer window origin */
		*(u_int *)data = 0;
		break;

	case FBIO_GETDISPSTART:	/* get display start address */
		((video_display_start_t *)data)->x = 0;
		((video_display_start_t *)data)->y = 0;
		break;

	case FBIO_GETLINEWIDTH:	/* get scan line width in bytes */
		*(u_int *)data = info->fb_stride;
		break;

	case FBIO_BLANK:	/* blank display */
		if (vd->vd_driver->vd_blank == NULL)
			return (ENODEV);
		vd->vd_driver->vd_blank(vd, TC_BLACK);
		break;

	default:
		error = ENOIOCTL;
		break;
	}

	return (error);
}