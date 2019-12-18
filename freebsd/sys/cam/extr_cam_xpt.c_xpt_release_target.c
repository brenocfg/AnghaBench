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
struct cam_et {scalar_t__ refcount; struct cam_et* luns; int /*<<< orphan*/  luns_mtx; int /*<<< orphan*/  ed_entries; struct cam_eb* bus; } ;
struct cam_eb {int /*<<< orphan*/  eb_mtx; int /*<<< orphan*/  generation; int /*<<< orphan*/  et_entries; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  M_CAMXPT ; 
 int /*<<< orphan*/  TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct cam_et*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct cam_et*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  links ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xpt_release_bus (struct cam_eb*) ; 

__attribute__((used)) static void
xpt_release_target(struct cam_et *target)
{
	struct cam_eb *bus = target->bus;

	mtx_lock(&bus->eb_mtx);
	if (--target->refcount > 0) {
		mtx_unlock(&bus->eb_mtx);
		return;
	}
	TAILQ_REMOVE(&bus->et_entries, target, links);
	bus->generation++;
	mtx_unlock(&bus->eb_mtx);
	KASSERT(TAILQ_EMPTY(&target->ed_entries),
	    ("destroying target, but device list is not empty"));
	xpt_release_bus(bus);
	mtx_destroy(&target->luns_mtx);
	if (target->luns)
		free(target->luns, M_CAMXPT);
	free(target, M_CAMXPT);
}