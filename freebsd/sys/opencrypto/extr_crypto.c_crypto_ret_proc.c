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
struct bintime {int dummy; } ;
struct cryptop {scalar_t__ crp_seq; int /*<<< orphan*/  (* krp_callback ) (struct cryptop*) ;int /*<<< orphan*/  (* crp_callback ) (struct cryptop*) ;struct bintime crp_tstamp; } ;
struct crypto_ret_worker {scalar_t__ reorder_cur_seq; int /*<<< orphan*/  crp_ret_q; int /*<<< orphan*/ * cryptoretproc; int /*<<< orphan*/  crypto_ret_mtx; int /*<<< orphan*/  crp_ret_kq; int /*<<< orphan*/  crp_ordered_ret_q; } ;
struct cryptkop {scalar_t__ crp_seq; int /*<<< orphan*/  (* krp_callback ) (struct cryptop*) ;int /*<<< orphan*/  (* crp_callback ) (struct cryptop*) ;struct bintime crp_tstamp; } ;
struct TYPE_2__ {int /*<<< orphan*/  cs_rets; int /*<<< orphan*/  cs_finis; int /*<<< orphan*/  cs_cb; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_RETW_LOCK (struct crypto_ret_worker*) ; 
 int /*<<< orphan*/  CRYPTO_RETW_UNLOCK (struct crypto_ret_worker*) ; 
 int /*<<< orphan*/  PWAIT ; 
 struct cryptop* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct cryptop*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crp_next ; 
 int /*<<< orphan*/  crypto_finis (int /*<<< orphan*/ *) ; 
 scalar_t__ crypto_timing ; 
 int /*<<< orphan*/  crypto_tstat (int /*<<< orphan*/ *,struct bintime*) ; 
 TYPE_1__ cryptostats ; 
 int /*<<< orphan*/  krp_next ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct cryptop*) ; 
 int /*<<< orphan*/  stub2 (struct cryptop*) ; 
 int /*<<< orphan*/  stub3 (struct cryptop*) ; 

__attribute__((used)) static void
crypto_ret_proc(struct crypto_ret_worker *ret_worker)
{
	struct cryptop *crpt;
	struct cryptkop *krpt;

	CRYPTO_RETW_LOCK(ret_worker);
	for (;;) {
		/* Harvest return q's for completed ops */
		crpt = TAILQ_FIRST(&ret_worker->crp_ordered_ret_q);
		if (crpt != NULL) {
			if (crpt->crp_seq == ret_worker->reorder_cur_seq) {
				TAILQ_REMOVE(&ret_worker->crp_ordered_ret_q, crpt, crp_next);
				ret_worker->reorder_cur_seq++;
			} else {
				crpt = NULL;
			}
		}

		if (crpt == NULL) {
			crpt = TAILQ_FIRST(&ret_worker->crp_ret_q);
			if (crpt != NULL)
				TAILQ_REMOVE(&ret_worker->crp_ret_q, crpt, crp_next);
		}

		krpt = TAILQ_FIRST(&ret_worker->crp_ret_kq);
		if (krpt != NULL)
			TAILQ_REMOVE(&ret_worker->crp_ret_kq, krpt, krp_next);

		if (crpt != NULL || krpt != NULL) {
			CRYPTO_RETW_UNLOCK(ret_worker);
			/*
			 * Run callbacks unlocked.
			 */
			if (crpt != NULL) {
#ifdef CRYPTO_TIMING
				if (crypto_timing) {
					/*
					 * NB: We must copy the timestamp before
					 * doing the callback as the cryptop is
					 * likely to be reclaimed.
					 */
					struct bintime t = crpt->crp_tstamp;
					crypto_tstat(&cryptostats.cs_cb, &t);
					crpt->crp_callback(crpt);
					crypto_tstat(&cryptostats.cs_finis, &t);
				} else
#endif
					crpt->crp_callback(crpt);
			}
			if (krpt != NULL)
				krpt->krp_callback(krpt);
			CRYPTO_RETW_LOCK(ret_worker);
		} else {
			/*
			 * Nothing more to be processed.  Sleep until we're
			 * woken because there are more returns to process.
			 */
			msleep(&ret_worker->crp_ret_q, &ret_worker->crypto_ret_mtx, PWAIT,
				"crypto_ret_wait", 0);
			if (ret_worker->cryptoretproc == NULL)
				break;
			cryptostats.cs_rets++;
		}
	}
	CRYPTO_RETW_UNLOCK(ret_worker);

	crypto_finis(&ret_worker->crp_ret_q);
}