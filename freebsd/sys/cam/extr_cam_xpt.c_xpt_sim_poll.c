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
struct cam_sim {int /*<<< orphan*/  (* sim_poll ) (struct cam_sim*) ;struct mtx* mtx; } ;

/* Variables and functions */
 int /*<<< orphan*/  camisr_runqueue () ; 
 int /*<<< orphan*/  mtx_lock (struct mtx*) ; 
 int /*<<< orphan*/  mtx_unlock (struct mtx*) ; 
 int /*<<< orphan*/  stub1 (struct cam_sim*) ; 

void
xpt_sim_poll(struct cam_sim *sim)
{
	struct mtx *mtx;

	mtx = sim->mtx;
	if (mtx)
		mtx_lock(mtx);
	(*(sim->sim_poll))(sim);
	if (mtx)
		mtx_unlock(mtx);
	camisr_runqueue();
}