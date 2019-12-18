#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct wf2qp_si {int wsum; int inv_wsum; int /*<<< orphan*/  sch_heap; int /*<<< orphan*/  ne_heap; int /*<<< orphan*/  V; int /*<<< orphan*/  idle_heap; } ;
struct wf2qp_queue {scalar_t__ S; scalar_t__ F; } ;
struct TYPE_6__ {int /*<<< orphan*/ * head; } ;
struct dn_queue {TYPE_3__ mq; TYPE_2__* fs; scalar_t__ _si; } ;
struct TYPE_4__ {scalar_t__* par; } ;
struct TYPE_5__ {TYPE_1__ fs; } ;

/* Variables and functions */
 scalar_t__ DN_KEY_LT (int /*<<< orphan*/ ,scalar_t__) ; 
 int ONE_FP ; 
 int /*<<< orphan*/  heap_extract (int /*<<< orphan*/ *,struct dn_queue*) ; 

__attribute__((used)) static int
wf2qp_free_queue(struct dn_queue *q)
{
	struct wf2qp_queue *alg_fq = (struct wf2qp_queue *)q;
	struct wf2qp_si *si = (struct wf2qp_si *)(q->_si + 1);

	if (alg_fq->S >= alg_fq->F + 1)
		return 0;	/* nothing to do, not in any heap */
	si->wsum -= q->fs->fs.par[0];
	if (si->wsum > 0)
		si->inv_wsum = ONE_FP/si->wsum;

	/* extract from the heap. XXX TODO we may need to adjust V
	 * to make sure the invariants hold.
	 */
	if (q->mq.head == NULL) {
		heap_extract(&si->idle_heap, q);
	} else if (DN_KEY_LT(si->V, alg_fq->S)) {
		heap_extract(&si->ne_heap, q);
	} else {
		heap_extract(&si->sch_heap, q);
	}
	return 0;
}