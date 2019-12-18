#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * csw; int /*<<< orphan*/  dev_ref; struct cdev* cdev; } ;
struct TYPE_5__ {TYPE_1__ dev; } ;
struct xbb_softc {int /*<<< orphan*/  dev_name; int /*<<< orphan*/  dev; int /*<<< orphan*/  media_size; int /*<<< orphan*/  sector_size; TYPE_3__* vn; TYPE_2__ backend; int /*<<< orphan*/  dispatch_io; int /*<<< orphan*/  device_type; } ;
struct vattr {int dummy; } ;
struct cdevsw {int (* d_ioctl ) (struct cdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct cdev {struct cdevsw* si_devsw; } ;
typedef  int /*<<< orphan*/  caddr_t ;
struct TYPE_6__ {struct cdev* v_rdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIOCGMEDIASIZE ; 
 int /*<<< orphan*/  DIOCGSECTORSIZE ; 
 int ENODEV ; 
 int /*<<< orphan*/  FREAD ; 
 int /*<<< orphan*/  NOCRED ; 
 int VOP_GETATTR (TYPE_3__*,struct vattr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XBB_TYPE_DISK ; 
 int /*<<< orphan*/  curthread ; 
 int /*<<< orphan*/ * dev_refthread (struct cdev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int stub1 (struct cdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub2 (struct cdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xbb_dispatch_dev ; 
 int /*<<< orphan*/  xenbus_dev_fatal (int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
xbb_open_dev(struct xbb_softc *xbb)
{
	struct vattr   vattr;
	struct cdev   *dev;
	struct cdevsw *devsw;
	int	       error;

	xbb->device_type = XBB_TYPE_DISK;
	xbb->dispatch_io = xbb_dispatch_dev;
	xbb->backend.dev.cdev = xbb->vn->v_rdev;
	xbb->backend.dev.csw = dev_refthread(xbb->backend.dev.cdev,
					     &xbb->backend.dev.dev_ref);
	if (xbb->backend.dev.csw == NULL)
		panic("Unable to retrieve device switch");

	error = VOP_GETATTR(xbb->vn, &vattr, NOCRED);
	if (error) {
		xenbus_dev_fatal(xbb->dev, error, "error getting "
				 "vnode attributes for device %s",
				 xbb->dev_name);
		return (error);
	}


	dev = xbb->vn->v_rdev;
	devsw = dev->si_devsw;
	if (!devsw->d_ioctl) {
		xenbus_dev_fatal(xbb->dev, ENODEV, "no d_ioctl for "
				 "device %s!", xbb->dev_name);
		return (ENODEV);
	}

	error = devsw->d_ioctl(dev, DIOCGSECTORSIZE,
			       (caddr_t)&xbb->sector_size, FREAD,
			       curthread);
	if (error) {
		xenbus_dev_fatal(xbb->dev, error,
				 "error calling ioctl DIOCGSECTORSIZE "
				 "for device %s", xbb->dev_name);
		return (error);
	}

	error = devsw->d_ioctl(dev, DIOCGMEDIASIZE,
			       (caddr_t)&xbb->media_size, FREAD,
			       curthread);
	if (error) {
		xenbus_dev_fatal(xbb->dev, error,
				 "error calling ioctl DIOCGMEDIASIZE "
				 "for device %s", xbb->dev_name);
		return (error);
	}

	return (0);
}