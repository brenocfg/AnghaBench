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
struct cam_sim {scalar_t__ refcount; int /*<<< orphan*/  devq; struct mtx* mtx; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  M_CAMSIM ; 
 int /*<<< orphan*/  PRIBIO ; 
 struct mtx cam_sim_free_mtx ; 
 int /*<<< orphan*/  cam_simq_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct cam_sim*,int /*<<< orphan*/ ) ; 
 int msleep (struct cam_sim*,struct mtx*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_assert (struct mtx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (struct mtx*) ; 
 int /*<<< orphan*/  mtx_unlock (struct mtx*) ; 

void
cam_sim_free(struct cam_sim *sim, int free_devq)
{
	struct mtx *mtx = sim->mtx;
	int error;

	if (mtx) {
		mtx_assert(mtx, MA_OWNED);
	} else {
		mtx = &cam_sim_free_mtx;
		mtx_lock(mtx);
	}
	sim->refcount--;
	if (sim->refcount > 0) {
		error = msleep(sim, mtx, PRIBIO, "simfree", 0);
		KASSERT(error == 0, ("invalid error value for msleep(9)"));
	}
	KASSERT(sim->refcount == 0, ("sim->refcount == 0"));
	if (sim->mtx == NULL)
		mtx_unlock(mtx);

	if (free_devq)
		cam_simq_free(sim->devq);
	free(sim, M_CAMSIM);
}