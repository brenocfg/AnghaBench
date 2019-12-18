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
struct TYPE_5__ {int /*<<< orphan*/ * cred; } ;
struct TYPE_4__ {int /*<<< orphan*/ * cdev; int /*<<< orphan*/ * csw; int /*<<< orphan*/  dev_ref; } ;
struct TYPE_6__ {TYPE_2__ file; TYPE_1__ dev; } ;
struct xbb_softc {int flags; int device_type; TYPE_3__ backend; int /*<<< orphan*/ * vn; int /*<<< orphan*/  dev_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DROP_GIANT () ; 
 int FREAD ; 
 int FWRITE ; 
 int /*<<< orphan*/  NOCRED ; 
 int /*<<< orphan*/  PICKUP_GIANT () ; 
 int XBBF_READ_ONLY ; 
#define  XBB_TYPE_DISK 130 
#define  XBB_TYPE_FILE 129 
#define  XBB_TYPE_NONE 128 
 int /*<<< orphan*/  crfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  curthread ; 
 int /*<<< orphan*/  dev_relthread (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  vn_close (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
xbb_close_backend(struct xbb_softc *xbb)
{
	DROP_GIANT();
	DPRINTF("closing dev=%s\n", xbb->dev_name);
	if (xbb->vn) {
		int flags = FREAD;

		if ((xbb->flags & XBBF_READ_ONLY) == 0)
			flags |= FWRITE;

		switch (xbb->device_type) {
		case XBB_TYPE_DISK:
			if (xbb->backend.dev.csw) {
				dev_relthread(xbb->backend.dev.cdev,
					      xbb->backend.dev.dev_ref);
				xbb->backend.dev.csw  = NULL;
				xbb->backend.dev.cdev = NULL;
			}
			break;
		case XBB_TYPE_FILE:
			break;
		case XBB_TYPE_NONE:
		default:
			panic("Unexpected backend type.");
			break;
		}

		(void)vn_close(xbb->vn, flags, NOCRED, curthread);
		xbb->vn = NULL;

		switch (xbb->device_type) {
		case XBB_TYPE_DISK:
			break;
		case XBB_TYPE_FILE:
			if (xbb->backend.file.cred != NULL) {
				crfree(xbb->backend.file.cred);
				xbb->backend.file.cred = NULL;
			}
			break;
		case XBB_TYPE_NONE:
		default:
			panic("Unexpected backend type.");
			break;
		}
	}
	PICKUP_GIANT();
}