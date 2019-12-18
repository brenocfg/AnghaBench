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
struct sge_fl {int flags; } ;
struct adapter {int /*<<< orphan*/  sfl_lock; int /*<<< orphan*/  sfl_callout; int /*<<< orphan*/  sfl; } ;

/* Variables and functions */
 int FL_DOOMED ; 
 int /*<<< orphan*/  FL_LOCK (struct sge_fl*) ; 
 int FL_STARVING ; 
 int /*<<< orphan*/  FL_UNLOCK (struct sge_fl*) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct sge_fl*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct adapter*) ; 
 int hz ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refill_sfl ; 

__attribute__((used)) static void
add_fl_to_sfl(struct adapter *sc, struct sge_fl *fl)
{
	mtx_lock(&sc->sfl_lock);
	FL_LOCK(fl);
	if ((fl->flags & FL_DOOMED) == 0) {
		fl->flags |= FL_STARVING;
		TAILQ_INSERT_TAIL(&sc->sfl, fl, link);
		callout_reset(&sc->sfl_callout, hz / 5, refill_sfl, sc);
	}
	FL_UNLOCK(fl);
	mtx_unlock(&sc->sfl_lock);
}