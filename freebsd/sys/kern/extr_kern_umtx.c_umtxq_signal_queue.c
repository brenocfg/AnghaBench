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
struct umtxq_queue {int /*<<< orphan*/  head; } ;
struct umtx_q {int dummy; } ;
struct umtx_key {int dummy; } ;

/* Variables and functions */
 struct umtx_q* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UMTXQ_LOCKED_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  umtxq_getchain (struct umtx_key*) ; 
 struct umtxq_queue* umtxq_queue_lookup (struct umtx_key*,int) ; 
 int /*<<< orphan*/  umtxq_remove_queue (struct umtx_q*,int) ; 
 int /*<<< orphan*/  wakeup (struct umtx_q*) ; 

__attribute__((used)) static int
umtxq_signal_queue(struct umtx_key *key, int n_wake, int q)
{
	struct umtxq_queue *uh;
	struct umtx_q *uq;
	int ret;

	ret = 0;
	UMTXQ_LOCKED_ASSERT(umtxq_getchain(key));
	uh = umtxq_queue_lookup(key, q);
	if (uh != NULL) {
		while ((uq = TAILQ_FIRST(&uh->head)) != NULL) {
			umtxq_remove_queue(uq, q);
			wakeup(uq);
			if (++ret >= n_wake)
				return (ret);
		}
	}
	return (ret);
}