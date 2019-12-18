#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vm_pagequeue {int /*<<< orphan*/  pq_pdpages; int /*<<< orphan*/  pq_pl; } ;
struct scan_state {scalar_t__ scanned; TYPE_1__* marker; struct vm_pagequeue* pq; } ;
struct TYPE_5__ {int /*<<< orphan*/  q; } ;
struct TYPE_4__ {int aflags; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int PGA_ENQUEUED ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_2__ plinks ; 
 int /*<<< orphan*/  vm_page_aflag_clear (TYPE_1__*,int) ; 
 int /*<<< orphan*/  vm_pagequeue_assert_locked (struct vm_pagequeue*) ; 

__attribute__((used)) static void
vm_pageout_end_scan(struct scan_state *ss)
{
	struct vm_pagequeue *pq;

	pq = ss->pq;
	vm_pagequeue_assert_locked(pq);
	KASSERT((ss->marker->aflags & PGA_ENQUEUED) != 0,
	    ("marker %p not enqueued", ss->marker));

	TAILQ_REMOVE(&pq->pq_pl, ss->marker, plinks.q);
	vm_page_aflag_clear(ss->marker, PGA_ENQUEUED);
	pq->pq_pdpages += ss->scanned;
}