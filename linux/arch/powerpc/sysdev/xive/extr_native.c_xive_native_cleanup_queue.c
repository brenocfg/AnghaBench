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
typedef  size_t u8 ;
struct xive_q {int /*<<< orphan*/ * qpage; } ;
struct xive_cpu {struct xive_q* queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  __xive_native_disable_queue (int /*<<< orphan*/ ,struct xive_q*,size_t) ; 
 int /*<<< orphan*/  free_pages (unsigned long,unsigned int) ; 
 int /*<<< orphan*/  get_hard_smp_processor_id (unsigned int) ; 
 unsigned int xive_alloc_order (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xive_queue_shift ; 

__attribute__((used)) static void xive_native_cleanup_queue(unsigned int cpu, struct xive_cpu *xc, u8 prio)
{
	struct xive_q *q = &xc->queue[prio];
	unsigned int alloc_order;

	/*
	 * We use the variant with no iounmap as this is called on exec
	 * from an IPI and iounmap isn't safe
	 */
	__xive_native_disable_queue(get_hard_smp_processor_id(cpu), q, prio);
	alloc_order = xive_alloc_order(xive_queue_shift);
	free_pages((unsigned long)q->qpage, alloc_order);
	q->qpage = NULL;
}