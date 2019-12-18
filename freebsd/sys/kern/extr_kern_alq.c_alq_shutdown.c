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
struct alq {int aq_flags; int /*<<< orphan*/  aq_cred; int /*<<< orphan*/  aq_vp; int /*<<< orphan*/  aq_mtx; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALD_LOCK () ; 
 int /*<<< orphan*/  ALD_UNLOCK () ; 
 int /*<<< orphan*/  ALQ_LOCK (struct alq*) ; 
 int /*<<< orphan*/  ALQ_UNLOCK (struct alq*) ; 
 int AQ_ACTIVE ; 
 int AQ_SHUTDOWN ; 
 int AQ_WANTED ; 
 int /*<<< orphan*/  FWRITE ; 
 scalar_t__ HAS_PENDING_DATA (struct alq*) ; 
 int /*<<< orphan*/  ald_activate (struct alq*) ; 
 int /*<<< orphan*/  crfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  curthread ; 
 int /*<<< orphan*/  msleep_spin (struct alq*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vn_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
alq_shutdown(struct alq *alq)
{
	ALQ_LOCK(alq);

	/* Stop any new writers. */
	alq->aq_flags |= AQ_SHUTDOWN;

	/*
	 * If the ALQ isn't active but has unwritten data (possible if
	 * the ALQ_NOACTIVATE flag has been used), explicitly activate the
	 * ALQ here so that the pending data gets flushed by the ald_daemon.
	 */
	if (!(alq->aq_flags & AQ_ACTIVE) && HAS_PENDING_DATA(alq)) {
		alq->aq_flags |= AQ_ACTIVE;
		ALQ_UNLOCK(alq);
		ALD_LOCK();
		ald_activate(alq);
		ALD_UNLOCK();
		ALQ_LOCK(alq);
	}

	/* Drain IO */
	while (alq->aq_flags & AQ_ACTIVE) {
		alq->aq_flags |= AQ_WANTED;
		msleep_spin(alq, &alq->aq_mtx, "aldclose", 0);
	}
	ALQ_UNLOCK(alq);

	vn_close(alq->aq_vp, FWRITE, alq->aq_cred,
	    curthread);
	crfree(alq->aq_cred);
}