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
struct hisi_qm {TYPE_2__* ops; int /*<<< orphan*/  ver; TYPE_1__* pdev; } ;
struct TYPE_4__ {int (* hw_error_handle ) (struct hisi_qm*) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int PCI_ERS_RESULT_NONE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int stub1 (struct hisi_qm*) ; 

int hisi_qm_hw_error_handle(struct hisi_qm *qm)
{
	if (!qm->ops->hw_error_handle) {
		dev_err(&qm->pdev->dev, "QM version %d doesn't support hw error report!\n",
			qm->ver);
		return PCI_ERS_RESULT_NONE;
	}

	return qm->ops->hw_error_handle(qm);
}