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
struct hisi_qm {scalar_t__ ver; TYPE_1__* pdev; scalar_t__ io_base; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 unsigned int BIT (int /*<<< orphan*/ ) ; 
 scalar_t__ QM_CACHE_WB_DONE ; 
 scalar_t__ QM_CACHE_WB_START ; 
 scalar_t__ QM_HW_V2 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ readl_relaxed_poll_timeout (scalar_t__,unsigned int,unsigned int,int,int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void hisi_qm_cache_wb(struct hisi_qm *qm)
{
	unsigned int val;

	if (qm->ver == QM_HW_V2) {
		writel(0x1, qm->io_base + QM_CACHE_WB_START);
		if (readl_relaxed_poll_timeout(qm->io_base + QM_CACHE_WB_DONE,
					       val, val & BIT(0), 10, 1000))
			dev_err(&qm->pdev->dev, "QM writeback sqc cache fail!\n");
	}
}