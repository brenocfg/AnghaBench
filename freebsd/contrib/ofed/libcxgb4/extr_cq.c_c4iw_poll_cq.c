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
struct ibv_wc {int dummy; } ;
struct ibv_cq {int dummy; } ;
struct c4iw_cq {int /*<<< orphan*/  lock; int /*<<< orphan*/  cq; int /*<<< orphan*/  rhp; } ;

/* Variables and functions */
 int EAGAIN ; 
 int ENODATA ; 
 int /*<<< orphan*/  c4iw_flush_qps (int /*<<< orphan*/ ) ; 
 int c4iw_poll_cq_one (struct c4iw_cq*,struct ibv_wc*) ; 
 int /*<<< orphan*/  pthread_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ t4_cq_in_error (int /*<<< orphan*/ *) ; 
 int t4_cq_notempty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  t4_reset_cq_in_error (int /*<<< orphan*/ *) ; 
 struct c4iw_cq* to_c4iw_cq (struct ibv_cq*) ; 

int c4iw_poll_cq(struct ibv_cq *ibcq, int num_entries, struct ibv_wc *wc)
{
	struct c4iw_cq *chp;
	int npolled;
	int err = 0;

	chp = to_c4iw_cq(ibcq);

	if (t4_cq_in_error(&chp->cq)) {
		t4_reset_cq_in_error(&chp->cq);
		c4iw_flush_qps(chp->rhp);
	}

	if (!num_entries)
		return t4_cq_notempty(&chp->cq);

	pthread_spin_lock(&chp->lock);
	for (npolled = 0; npolled < num_entries; ++npolled) {
		do {
			err = c4iw_poll_cq_one(chp, wc + npolled);
		} while (err == -EAGAIN);
		if (err)
			break;
	}
	pthread_spin_unlock(&chp->lock);
	return !err || err == -ENODATA ? npolled : err;
}