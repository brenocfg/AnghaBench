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
struct hisi_qm {scalar_t__ ver; scalar_t__ io_base; TYPE_1__* pdev; } ;
struct hisi_zip {struct hisi_qm qm; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  HZIP_CORE_INT_DISABLE ; 
 scalar_t__ HZIP_CORE_INT_MASK ; 
 scalar_t__ HZIP_CORE_INT_SOURCE ; 
 scalar_t__ QM_HW_V1 ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void hisi_zip_hw_error_set_state(struct hisi_zip *hisi_zip, bool state)
{
	struct hisi_qm *qm = &hisi_zip->qm;

	if (qm->ver == QM_HW_V1) {
		writel(HZIP_CORE_INT_DISABLE, qm->io_base + HZIP_CORE_INT_MASK);
		dev_info(&qm->pdev->dev, "ZIP v%d does not support hw error handle\n",
			 qm->ver);
		return;
	}

	if (state) {
		/* clear ZIP hw error source if having */
		writel(HZIP_CORE_INT_DISABLE, hisi_zip->qm.io_base +
					      HZIP_CORE_INT_SOURCE);
		/* enable ZIP hw error interrupts */
		writel(0, hisi_zip->qm.io_base + HZIP_CORE_INT_MASK);
	} else {
		/* disable ZIP hw error interrupts */
		writel(HZIP_CORE_INT_DISABLE,
		       hisi_zip->qm.io_base + HZIP_CORE_INT_MASK);
	}
}