#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sge_rspq {int /*<<< orphan*/  unhandled_irqs; } ;
struct sge_qset {struct sge_rspq rspq; TYPE_1__* port; } ;
typedef  int /*<<< orphan*/  adapter_t ;
struct TYPE_2__ {int /*<<< orphan*/ * adapter; } ;

/* Variables and functions */
 scalar_t__ process_responses_gts (int /*<<< orphan*/ *,struct sge_rspq*) ; 

void
t3_intr_msix(void *data)
{
	struct sge_qset *qs = data;
	adapter_t *adap = qs->port->adapter;
	struct sge_rspq *rspq = &qs->rspq;

	if (process_responses_gts(adap, rspq) == 0)
		rspq->unhandled_irqs++;
}