#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vm_page_t ;
typedef  scalar_t__ uint8_t ;
struct vm_pagequeue {int dummy; } ;
struct vm_batchqueue {int bq_cnt; TYPE_1__** bq_pa; } ;
struct TYPE_3__ {scalar_t__ queue; } ;

/* Variables and functions */
 scalar_t__ __predict_false (int) ; 
 int /*<<< orphan*/  vm_batchqueue_init (struct vm_batchqueue*) ; 
 int /*<<< orphan*/  vm_pqbatch_process_page (struct vm_pagequeue*,TYPE_1__*) ; 

__attribute__((used)) static void
vm_pqbatch_process(struct vm_pagequeue *pq, struct vm_batchqueue *bq,
    uint8_t queue)
{
	vm_page_t m;
	int i;

	for (i = 0; i < bq->bq_cnt; i++) {
		m = bq->bq_pa[i];
		if (__predict_false(m->queue != queue))
			continue;
		vm_pqbatch_process_page(pq, m);
	}
	vm_batchqueue_init(bq);
}