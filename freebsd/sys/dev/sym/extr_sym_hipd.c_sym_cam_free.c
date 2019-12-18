#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* hcb_p ;
struct TYPE_3__ {int /*<<< orphan*/ * path; int /*<<< orphan*/ * sim; int /*<<< orphan*/ * intr; int /*<<< orphan*/  irq_res; int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_NOTOWNED ; 
 int /*<<< orphan*/  SYM_LOCK () ; 
 int /*<<< orphan*/  SYM_LOCK_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYM_UNLOCK () ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cam_sim_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cam_sim_path (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xpt_bus_deregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_free_path (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sym_cam_free(hcb_p np)
{

	SYM_LOCK_ASSERT(MA_NOTOWNED);

	if (np->intr) {
		bus_teardown_intr(np->device, np->irq_res, np->intr);
		np->intr = NULL;
	}

	SYM_LOCK();

	if (np->sim) {
		xpt_bus_deregister(cam_sim_path(np->sim));
		cam_sim_free(np->sim, /*free_devq*/ TRUE);
		np->sim = NULL;
	}
	if (np->path) {
		xpt_free_path(np->path);
		np->path = NULL;
	}

	SYM_UNLOCK();
}