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
struct mpr_softc {int /*<<< orphan*/  mpr_mtx; } ;
struct mpr_command {scalar_t__ cm_state; struct mpr_softc* cm_sc; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 scalar_t__ MPR_CM_STATE_BUSY ; 
 scalar_t__ MPR_CM_STATE_INQUEUE ; 
 int MPR_INFO ; 
 int MPR_RECOVERY ; 
 int /*<<< orphan*/  mpr_reinit (struct mpr_softc*) ; 
 int /*<<< orphan*/  mprsas_log_command (struct mpr_command*,int,char*,struct mpr_command*) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mprsas_tm_timeout(void *data)
{
	struct mpr_command *tm = data;
	struct mpr_softc *sc = tm->cm_sc;

	mtx_assert(&sc->mpr_mtx, MA_OWNED);

	mprsas_log_command(tm, MPR_INFO|MPR_RECOVERY, "task mgmt %p timed "
	    "out\n", tm);

	KASSERT(tm->cm_state == MPR_CM_STATE_INQUEUE,
	    ("command not inqueue\n"));

	tm->cm_state = MPR_CM_STATE_BUSY;
	mpr_reinit(sc);
}