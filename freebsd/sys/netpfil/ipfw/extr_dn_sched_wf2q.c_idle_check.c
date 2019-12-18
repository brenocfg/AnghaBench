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
struct dn_heap {scalar_t__ elements; } ;
struct wf2qp_si {int wsum; int inv_wsum; int /*<<< orphan*/  V; struct dn_heap idle_heap; } ;
struct wf2qp_queue {scalar_t__ F; scalar_t__ S; } ;
struct dn_queue {TYPE_2__* fs; } ;
struct TYPE_6__ {struct dn_queue* object; int /*<<< orphan*/  key; } ;
struct TYPE_4__ {scalar_t__* par; } ;
struct TYPE_5__ {TYPE_1__ fs; } ;

/* Variables and functions */
 scalar_t__ DN_KEY_LT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* HEAP_TOP (struct dn_heap*) ; 
 int ONE_FP ; 
 int /*<<< orphan*/  heap_extract (struct dn_heap*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
idle_check(struct wf2qp_si *si, int n, int force)
{
    struct dn_heap *h = &si->idle_heap;
    while (n-- > 0 && h->elements > 0 &&
		(force || DN_KEY_LT(HEAP_TOP(h)->key, si->V))) {
	struct dn_queue *q = HEAP_TOP(h)->object;
        struct wf2qp_queue *alg_fq = (struct wf2qp_queue *)q;

        heap_extract(h, NULL);
        /* XXX to let the flowset delete the queue we should
	 * mark it as 'unused' by the scheduler.
	 */
        alg_fq->S = alg_fq->F + 1; /* Mark timestamp as invalid. */
        si->wsum -= q->fs->fs.par[0];	/* adjust sum of weights */
	if (si->wsum > 0)
		si->inv_wsum = ONE_FP/si->wsum;
    }
}