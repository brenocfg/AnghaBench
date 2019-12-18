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
struct alq {int aq_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALD_LOCK () ; 
 int /*<<< orphan*/  ALD_UNLOCK () ; 
 int /*<<< orphan*/  ALQ_LOCK (struct alq*) ; 
 int /*<<< orphan*/  ALQ_UNLOCK (struct alq*) ; 
 int AQ_ACTIVE ; 
 int AQ_FLUSHING ; 
 scalar_t__ HAS_PENDING_DATA (struct alq*) ; 
 int /*<<< orphan*/  ald_deactivate (struct alq*) ; 
 int alq_doio (struct alq*) ; 
 int /*<<< orphan*/  wakeup_one (struct alq*) ; 

void
alq_flush(struct alq *alq)
{
	int needwakeup = 0;

	ALD_LOCK();
	ALQ_LOCK(alq);

	/*
	 * Pull the lever iff there is data to flush and we're
	 * not already in the middle of a flush operation.
	 */
	if (HAS_PENDING_DATA(alq) && !(alq->aq_flags & AQ_FLUSHING)) {
		if (alq->aq_flags & AQ_ACTIVE)
			ald_deactivate(alq);

		ALD_UNLOCK();
		needwakeup = alq_doio(alq);
	} else
		ALD_UNLOCK();

	ALQ_UNLOCK(alq);

	if (needwakeup)
		wakeup_one(alq);
}