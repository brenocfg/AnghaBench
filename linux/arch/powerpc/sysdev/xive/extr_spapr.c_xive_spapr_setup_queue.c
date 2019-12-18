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
struct xive_q {int dummy; } ;
struct xive_cpu {struct xive_q* queue; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_hard_smp_processor_id (unsigned int) ; 
 int /*<<< orphan*/ * xive_queue_page_alloc (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xive_queue_shift ; 
 int xive_spapr_configure_queue (int /*<<< orphan*/ ,struct xive_q*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xive_spapr_setup_queue(unsigned int cpu, struct xive_cpu *xc,
				  u8 prio)
{
	struct xive_q *q = &xc->queue[prio];
	__be32 *qpage;

	qpage = xive_queue_page_alloc(cpu, xive_queue_shift);
	if (IS_ERR(qpage))
		return PTR_ERR(qpage);

	return xive_spapr_configure_queue(get_hard_smp_processor_id(cpu),
					  q, prio, qpage, xive_queue_shift);
}