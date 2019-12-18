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
typedef  int u32 ;
struct hisi_qm_hw_error {int int_msk; scalar_t__ msg; } ;
struct hisi_qm {int msi_mask; scalar_t__ io_base; TYPE_1__* pdev; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ QM_ABNORMAL_INT_SOURCE ; 
 scalar_t__ QM_ABNORMAL_INT_STATUS ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,scalar_t__,int) ; 
 struct hisi_qm_hw_error* qm_hw_error ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static irqreturn_t qm_abnormal_irq(int irq, void *data)
{
	const struct hisi_qm_hw_error *err = qm_hw_error;
	struct hisi_qm *qm = data;
	struct device *dev = &qm->pdev->dev;
	u32 error_status, tmp;

	/* read err sts */
	tmp = readl(qm->io_base + QM_ABNORMAL_INT_STATUS);
	error_status = qm->msi_mask & tmp;

	while (err->msg) {
		if (err->int_msk & error_status)
			dev_err(dev, "%s [error status=0x%x] found\n",
				err->msg, err->int_msk);

		err++;
	}

	/* clear err sts */
	writel(error_status, qm->io_base + QM_ABNORMAL_INT_SOURCE);

	return IRQ_HANDLED;
}