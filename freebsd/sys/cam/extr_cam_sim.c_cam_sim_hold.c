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
struct mtx {int dummy; } ;
struct cam_sim {int refcount; struct mtx* mtx; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 struct mtx cam_sim_free_mtx ; 
 int /*<<< orphan*/  mtx_lock (struct mtx*) ; 
 int /*<<< orphan*/  mtx_owned (struct mtx*) ; 
 int /*<<< orphan*/  mtx_unlock (struct mtx*) ; 

void
cam_sim_hold(struct cam_sim *sim)
{
	struct mtx *mtx = sim->mtx;

	if (mtx) {
		if (!mtx_owned(mtx))
			mtx_lock(mtx);
		else
			mtx = NULL;
	} else {
		mtx = &cam_sim_free_mtx;
		mtx_lock(mtx);
	}
	KASSERT(sim->refcount >= 1, ("sim->refcount >= 1"));
	sim->refcount++;
	if (mtx)
		mtx_unlock(mtx);
}