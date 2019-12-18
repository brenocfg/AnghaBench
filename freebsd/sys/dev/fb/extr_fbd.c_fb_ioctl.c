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
struct TYPE_2__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
typedef  TYPE_1__ video_display_start_t ;
typedef  int u_long ;
typedef  int /*<<< orphan*/  u_int ;
struct thread {int dummy; } ;
struct fbtype {int dummy; } ;
struct fb_info {int (* setblankmode ) (int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  fb_priv; int /*<<< orphan*/  fb_stride; } ;
struct cdev {struct fb_info* si_drv1; } ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int ENOIOCTL ; 
#define  FBIOGTYPE 132 
#define  FBIO_BLANK 131 
#define  FBIO_GETDISPSTART 130 
#define  FBIO_GETLINEWIDTH 129 
#define  FBIO_GETWINORG 128 
 int /*<<< orphan*/  bcopy (struct fb_info*,struct fbtype*,int) ; 
 int stub1 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
fb_ioctl(struct cdev *dev, u_long cmd, caddr_t data, int fflag,
    struct thread *td)
{
	struct fb_info *info;
	int error;

	error = 0;
	info = dev->si_drv1;

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
		if (info->setblankmode != NULL)
			error = info->setblankmode(info->fb_priv, *(int *)data);
		break;

	default:
		error = ENOIOCTL;
		break;
	}
	return (error);
}