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
struct umtxq_queue {scalar_t__ length; int /*<<< orphan*/  head; } ;
struct umtxq_chain {int /*<<< orphan*/  uc_spare_queue; int /*<<< orphan*/  length; } ;
struct umtx_q {int uq_flags; struct umtxq_queue* uq_cur_queue; struct umtxq_queue* uq_spare_queue; int /*<<< orphan*/  uq_key; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 struct umtxq_queue* LIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct umtxq_queue*,int /*<<< orphan*/ ) ; 
 scalar_t__ TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct umtx_q*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UMTXQ_LOCKED_ASSERT (struct umtxq_chain*) ; 
 int UQF_UMTXQ ; 
 int /*<<< orphan*/  link ; 
 struct umtxq_chain* umtxq_getchain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uq_link ; 

__attribute__((used)) static inline void
umtxq_remove_queue(struct umtx_q *uq, int q)
{
	struct umtxq_chain *uc;
	struct umtxq_queue *uh;

	uc = umtxq_getchain(&uq->uq_key);
	UMTXQ_LOCKED_ASSERT(uc);
	if (uq->uq_flags & UQF_UMTXQ) {
		uh = uq->uq_cur_queue;
		TAILQ_REMOVE(&uh->head, uq, uq_link);
		uh->length--;
		uq->uq_flags &= ~UQF_UMTXQ;
		if (TAILQ_EMPTY(&uh->head)) {
			KASSERT(uh->length == 0,
			    ("inconsistent umtxq_queue length"));
#ifdef UMTX_PROFILING
			uc->length--;
#endif
			LIST_REMOVE(uh, link);
		} else {
			uh = LIST_FIRST(&uc->uc_spare_queue);
			KASSERT(uh != NULL, ("uc_spare_queue is empty"));
			LIST_REMOVE(uh, link);
		}
		uq->uq_spare_queue = uh;
		uq->uq_cur_queue = NULL;
	}
}