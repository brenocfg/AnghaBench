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
typedef  scalar_t__ u32 ;
struct xive_q {scalar_t__ idx; scalar_t__ toggle; int /*<<< orphan*/  msk; int /*<<< orphan*/  qpage; } ;
struct kvmppc_xive {int dummy; } ;

/* Variables and functions */
 scalar_t__ XICS_IPI ; 
 scalar_t__ __xive_read_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  xive_pre_save_set_queued (struct kvmppc_xive*,scalar_t__) ; 

__attribute__((used)) static void xive_pre_save_queue(struct kvmppc_xive *xive, struct xive_q *q)
{
	u32 idx = q->idx;
	u32 toggle = q->toggle;
	u32 irq;

	do {
		irq = __xive_read_eq(q->qpage, q->msk, &idx, &toggle);
		if (irq > XICS_IPI)
			xive_pre_save_set_queued(xive, irq);
	} while(irq);
}