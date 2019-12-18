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
typedef  int /*<<< orphan*/ * vm_page_t ;
struct vm_pagequeue {int dummy; } ;
struct vm_batchqueue {int dummy; } ;
struct scan_state {struct vm_pagequeue* pq; } ;

/* Variables and functions */
 int /*<<< orphan*/  vm_batchqueue_init (struct vm_batchqueue*) ; 
 scalar_t__ vm_batchqueue_insert (struct vm_batchqueue*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vm_batchqueue_pop (struct vm_batchqueue*) ; 
 scalar_t__ vm_pageout_reinsert_inactive_page (struct scan_state*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vm_pagequeue_cnt_add (struct vm_pagequeue*,int) ; 
 int /*<<< orphan*/  vm_pagequeue_lock (struct vm_pagequeue*) ; 
 int /*<<< orphan*/  vm_pagequeue_unlock (struct vm_pagequeue*) ; 

__attribute__((used)) static void
vm_pageout_reinsert_inactive(struct scan_state *ss, struct vm_batchqueue *bq,
    vm_page_t m)
{
	struct vm_pagequeue *pq;
	int delta;

	delta = 0;
	pq = ss->pq;

	if (m != NULL) {
		if (vm_batchqueue_insert(bq, m))
			return;
		vm_pagequeue_lock(pq);
		delta += vm_pageout_reinsert_inactive_page(ss, m);
	} else
		vm_pagequeue_lock(pq);
	while ((m = vm_batchqueue_pop(bq)) != NULL)
		delta += vm_pageout_reinsert_inactive_page(ss, m);
	vm_pagequeue_cnt_add(pq, delta);
	vm_pagequeue_unlock(pq);
	vm_batchqueue_init(bq);
}