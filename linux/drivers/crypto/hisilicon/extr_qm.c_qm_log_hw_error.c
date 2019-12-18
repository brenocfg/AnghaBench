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
struct hisi_qm {scalar_t__ io_base; TYPE_1__* pdev; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 scalar_t__ QM_ABNORMAL_INF00 ; 
 scalar_t__ QM_ABNORMAL_INF01 ; 
 int QM_DB_TIMEOUT ; 
 int QM_DB_TIMEOUT_TYPE ; 
 int QM_DB_TIMEOUT_TYPE_SHIFT ; 
 int QM_DB_TIMEOUT_VF ; 
 int QM_FIFO_OVERFLOW_TYPE ; 
 int QM_FIFO_OVERFLOW_TYPE_SHIFT ; 
 int QM_FIFO_OVERFLOW_VF ; 
 int QM_OF_FIFO_OF ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/ * qm_db_timeout ; 
 int /*<<< orphan*/ * qm_fifo_overflow ; 
 struct hisi_qm_hw_error* qm_hw_error ; 
 int readl (scalar_t__) ; 

__attribute__((used)) static void qm_log_hw_error(struct hisi_qm *qm, u32 error_status)
{
	const struct hisi_qm_hw_error *err = qm_hw_error;
	struct device *dev = &qm->pdev->dev;
	u32 reg_val, type, vf_num;

	while (err->msg) {
		if (err->int_msk & error_status) {
			dev_err(dev, "%s [error status=0x%x] found\n",
				err->msg, err->int_msk);

			if (error_status & QM_DB_TIMEOUT) {
				reg_val = readl(qm->io_base +
						QM_ABNORMAL_INF01);
				type = (reg_val & QM_DB_TIMEOUT_TYPE) >>
				       QM_DB_TIMEOUT_TYPE_SHIFT;
				vf_num = reg_val & QM_DB_TIMEOUT_VF;
				dev_err(dev, "qm %s doorbell timeout in function %u\n",
					qm_db_timeout[type], vf_num);
			}

			if (error_status & QM_OF_FIFO_OF) {
				reg_val = readl(qm->io_base +
						QM_ABNORMAL_INF00);
				type = (reg_val & QM_FIFO_OVERFLOW_TYPE) >>
				       QM_FIFO_OVERFLOW_TYPE_SHIFT;
				vf_num = reg_val & QM_FIFO_OVERFLOW_VF;

				if (type < ARRAY_SIZE(qm_fifo_overflow))
					dev_err(dev, "qm %s fifo overflow in function %u\n",
						qm_fifo_overflow[type],
						vf_num);
				else
					dev_err(dev, "unknown error type\n");
			}
		}
		err++;
	}
}