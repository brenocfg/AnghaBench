#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct cam_sim {int dummy; } ;
struct cam_path {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  sim_lock; } ;
typedef  TYPE_1__ ocs_t ;
struct TYPE_9__ {struct cam_sim* sim; struct cam_path* path; int /*<<< orphan*/  targ_rsrc_wildcard; int /*<<< orphan*/  ldt; } ;
typedef  TYPE_2__ ocs_fcport ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  AC_LOST_DEVICE ; 
 int /*<<< orphan*/  FALSE ; 
 TYPE_2__* FCPORT (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cam_sim_free (struct cam_sim*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cam_sim_path (struct cam_sim*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_ldt_task (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_tgt_resource_abort (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xpt_async (int /*<<< orphan*/ ,struct cam_path*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xpt_bus_deregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_free_path (struct cam_path*) ; 

__attribute__((used)) static int32_t
ocs_detach_port(ocs_t *ocs, int32_t chan)
{
	ocs_fcport *fcp = NULL;
	struct cam_sim	*sim = NULL;
	struct cam_path	*path = NULL;
	fcp = FCPORT(ocs, chan);

	sim = fcp->sim;
	path = fcp->path;

	callout_drain(&fcp->ldt);
	ocs_ldt_task(fcp, 0);	

	if (fcp->sim) {
		mtx_lock(&ocs->sim_lock);
			ocs_tgt_resource_abort(ocs, &fcp->targ_rsrc_wildcard);
			if (path) {
				xpt_async(AC_LOST_DEVICE, path, NULL);
				xpt_free_path(path);
				fcp->path = NULL;
			}
			xpt_bus_deregister(cam_sim_path(sim));

			cam_sim_free(sim, FALSE);
			fcp->sim = NULL;
		mtx_unlock(&ocs->sim_lock);
	}
	
	return 0;
}