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
struct cam_eb {int refcount; int /*<<< orphan*/  eb_mtx; int /*<<< orphan*/  sim; int /*<<< orphan*/  et_entries; } ;
struct TYPE_2__ {int /*<<< orphan*/  bus_generation; int /*<<< orphan*/  xpt_busses; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  M_CAMXPT ; 
 int TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct cam_eb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cam_sim_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct cam_eb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  links ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xpt_lock_buses () ; 
 int /*<<< orphan*/  xpt_unlock_buses () ; 
 TYPE_1__ xsoftc ; 

__attribute__((used)) static void
xpt_release_bus(struct cam_eb *bus)
{

	xpt_lock_buses();
	KASSERT(bus->refcount >= 1, ("bus->refcount >= 1"));
	if (--bus->refcount > 0) {
		xpt_unlock_buses();
		return;
	}
	TAILQ_REMOVE(&xsoftc.xpt_busses, bus, links);
	xsoftc.bus_generation++;
	xpt_unlock_buses();
	KASSERT(TAILQ_EMPTY(&bus->et_entries),
	    ("destroying bus, but target list is not empty"));
	cam_sim_release(bus->sim);
	mtx_destroy(&bus->eb_mtx);
	free(bus, M_CAMXPT);
}