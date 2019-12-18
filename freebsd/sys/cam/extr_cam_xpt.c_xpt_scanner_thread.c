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
struct TYPE_6__ {int /*<<< orphan*/  path; } ;
union ccb {TYPE_3__ ccb_h; } ;
struct cam_path {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  tqe; } ;
struct TYPE_4__ {int /*<<< orphan*/  ccb_scanq; int /*<<< orphan*/  xpt_topo_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  PRIBIO ; 
 scalar_t__ TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 scalar_t__ TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 TYPE_2__ sim_links ; 
 int /*<<< orphan*/  xpt_action (union ccb*) ; 
 int /*<<< orphan*/  xpt_copy_path (struct cam_path*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_lock_buses () ; 
 int /*<<< orphan*/  xpt_path_lock (struct cam_path*) ; 
 int /*<<< orphan*/  xpt_path_unlock (struct cam_path*) ; 
 int /*<<< orphan*/  xpt_release_path (struct cam_path*) ; 
 int /*<<< orphan*/  xpt_unlock_buses () ; 
 TYPE_1__ xsoftc ; 

__attribute__((used)) static void
xpt_scanner_thread(void *dummy)
{
	union ccb	*ccb;
	struct cam_path	 path;

	xpt_lock_buses();
	for (;;) {
		if (TAILQ_EMPTY(&xsoftc.ccb_scanq))
			msleep(&xsoftc.ccb_scanq, &xsoftc.xpt_topo_lock, PRIBIO,
			       "-", 0);
		if ((ccb = (union ccb *)TAILQ_FIRST(&xsoftc.ccb_scanq)) != NULL) {
			TAILQ_REMOVE(&xsoftc.ccb_scanq, &ccb->ccb_h, sim_links.tqe);
			xpt_unlock_buses();

			/*
			 * Since lock can be dropped inside and path freed
			 * by completion callback even before return here,
			 * take our own path copy for reference.
			 */
			xpt_copy_path(&path, ccb->ccb_h.path);
			xpt_path_lock(&path);
			xpt_action(ccb);
			xpt_path_unlock(&path);
			xpt_release_path(&path);

			xpt_lock_buses();
		}
	}
}