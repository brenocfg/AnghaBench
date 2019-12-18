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
struct spu_queue {int /*<<< orphan*/  lock; int /*<<< orphan*/  qhandle; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,unsigned long,...) ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 unsigned long sun4v_ncs_gethead (int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  sun4v_ncs_sethead_marker (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static irqreturn_t mau_intr(int irq, void *dev_id)
{
	struct spu_queue *q = dev_id;
	unsigned long head, hv_ret;

	spin_lock(&q->lock);

	pr_err("CPU[%d]: Got MAU interrupt for qhdl[%lx]\n",
	       smp_processor_id(), q->qhandle);

	hv_ret = sun4v_ncs_gethead(q->qhandle, &head);

	pr_err("CPU[%d]: MAU gethead[%lx] hv_ret[%lu]\n",
	       smp_processor_id(), head, hv_ret);

	sun4v_ncs_sethead_marker(q->qhandle, head);

	spin_unlock(&q->lock);

	return IRQ_HANDLED;
}