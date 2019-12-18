#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  eq_head; } ;
struct hisi_qm {TYPE_2__ status; TYPE_1__* pdev; scalar_t__ io_base; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  QM_DOORBELL_CMD_EQ ; 
 scalar_t__ QM_VF_EQ_INT_SOURCE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  qm_db (struct hisi_qm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qm_irq_handler (int,void*) ; 
 scalar_t__ readl (scalar_t__) ; 

__attribute__((used)) static irqreturn_t qm_irq(int irq, void *data)
{
	struct hisi_qm *qm = data;

	if (readl(qm->io_base + QM_VF_EQ_INT_SOURCE))
		return qm_irq_handler(irq, data);

	dev_err(&qm->pdev->dev, "invalid int source\n");
	qm_db(qm, 0, QM_DOORBELL_CMD_EQ, qm->status.eq_head, 0);

	return IRQ_NONE;
}