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
typedef  scalar_t__ u32 ;
struct device {int dummy; } ;
struct cpt_device {int /*<<< orphan*/  reg_base; TYPE_1__* pdev; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPTX_PF_EXEC_BUSY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CPTX_PF_EXE_CTL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CPTX_PF_GX_EN (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ CPT_MAX_CORE_GROUPS ; 
 int /*<<< orphan*/  CSR_DELAY ; 
 scalar_t__ cpt_read_csr64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpt_write_csr64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cpt_disable_all_cores(struct cpt_device *cpt)
{
	u32 grp, timeout = 100;
	struct device *dev = &cpt->pdev->dev;

	/* Disengage the cores from groups */
	for (grp = 0; grp < CPT_MAX_CORE_GROUPS; grp++) {
		cpt_write_csr64(cpt->reg_base, CPTX_PF_GX_EN(0, grp), 0);
		udelay(CSR_DELAY);
	}

	grp = cpt_read_csr64(cpt->reg_base, CPTX_PF_EXEC_BUSY(0));
	while (grp) {
		dev_err(dev, "Cores still busy");
		grp = cpt_read_csr64(cpt->reg_base,
				     CPTX_PF_EXEC_BUSY(0));
		if (timeout--)
			break;

		udelay(CSR_DELAY);
	}
	/* Disable the cores */
	cpt_write_csr64(cpt->reg_base, CPTX_PF_EXE_CTL(0), 0);
}