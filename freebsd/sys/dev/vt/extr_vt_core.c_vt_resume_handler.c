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
struct vt_device {int /*<<< orphan*/  vd_flags; TYPE_1__* vd_driver; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* vd_resume ) (struct vt_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  VDF_SUSPENDED ; 
 int /*<<< orphan*/  stub1 (struct vt_device*) ; 

__attribute__((used)) static void
vt_resume_handler(void *priv)
{
	struct vt_device *vd;

	vd = priv;
	if (vd->vd_driver != NULL && vd->vd_driver->vd_resume != NULL)
		vd->vd_driver->vd_resume(vd);
	vd->vd_flags &= ~VDF_SUSPENDED;
}