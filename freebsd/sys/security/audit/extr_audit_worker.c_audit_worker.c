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
struct kaudit_record {int dummy; } ;
struct kaudit_queue {int dummy; } ;
struct TYPE_2__ {scalar_t__ aq_lowater; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 scalar_t__ TAILQ_EMPTY (struct kaudit_queue*) ; 
 struct kaudit_record* TAILQ_FIRST (struct kaudit_queue*) ; 
 int /*<<< orphan*/  TAILQ_INIT (struct kaudit_queue*) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (struct kaudit_queue*,struct kaudit_record*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (struct kaudit_queue*,struct kaudit_record*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  audit_free (struct kaudit_record*) ; 
 int /*<<< orphan*/  audit_mtx ; 
 struct kaudit_queue audit_q ; 
 scalar_t__ audit_q_len ; 
 TYPE_1__ audit_qctrl ; 
 int /*<<< orphan*/  audit_watermark_cv ; 
 int /*<<< orphan*/  audit_worker_cv ; 
 int /*<<< orphan*/  audit_worker_process_record (struct kaudit_record*) ; 
 int /*<<< orphan*/  cv_broadcast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cv_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  k_q ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
audit_worker(void *arg)
{
	struct kaudit_queue ar_worklist;
	struct kaudit_record *ar;
	int lowater_signal;

	TAILQ_INIT(&ar_worklist);
	mtx_lock(&audit_mtx);
	while (1) {
		mtx_assert(&audit_mtx, MA_OWNED);

		/*
		 * Wait for a record.
		 */
		while (TAILQ_EMPTY(&audit_q))
			cv_wait(&audit_worker_cv, &audit_mtx);

		/*
		 * If there are records in the global audit record queue,
		 * transfer them to a thread-local queue and process them
		 * one by one.  If we cross the low watermark threshold,
		 * signal any waiting processes that they may wake up and
		 * continue generating records.
		 */
		lowater_signal = 0;
		while ((ar = TAILQ_FIRST(&audit_q))) {
			TAILQ_REMOVE(&audit_q, ar, k_q);
			audit_q_len--;
			if (audit_q_len == audit_qctrl.aq_lowater)
				lowater_signal++;
			TAILQ_INSERT_TAIL(&ar_worklist, ar, k_q);
		}
		if (lowater_signal)
			cv_broadcast(&audit_watermark_cv);

		mtx_unlock(&audit_mtx);
		while ((ar = TAILQ_FIRST(&ar_worklist))) {
			TAILQ_REMOVE(&ar_worklist, ar, k_q);
			audit_worker_process_record(ar);
			audit_free(ar);
		}
		mtx_lock(&audit_mtx);
	}
}