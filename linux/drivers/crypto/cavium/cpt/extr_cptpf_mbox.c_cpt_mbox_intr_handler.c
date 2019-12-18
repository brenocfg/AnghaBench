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
typedef  unsigned long long u8 ;
typedef  unsigned long long u64 ;
struct cpt_device {TYPE_1__* pdev; int /*<<< orphan*/  reg_base; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPTX_PF_MBOX_INTX (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned long long CPT_MAX_VF_NUM ; 
 int /*<<< orphan*/  cpt_clear_mbox_intr (struct cpt_device*,unsigned long long) ; 
 int /*<<< orphan*/  cpt_handle_mbox_intr (struct cpt_device*,unsigned long long) ; 
 unsigned long long cpt_read_csr64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,unsigned long long,...) ; 

void cpt_mbox_intr_handler (struct cpt_device *cpt, int mbx)
{
	u64 intr;
	u8  vf;

	intr = cpt_read_csr64(cpt->reg_base, CPTX_PF_MBOX_INTX(0, 0));
	dev_dbg(&cpt->pdev->dev, "PF interrupt Mbox%d 0x%llx\n", mbx, intr);
	for (vf = 0; vf < CPT_MAX_VF_NUM; vf++) {
		if (intr & (1ULL << vf)) {
			dev_dbg(&cpt->pdev->dev, "Intr from VF %d\n", vf);
			cpt_handle_mbox_intr(cpt, vf);
			cpt_clear_mbox_intr(cpt, vf);
		}
	}
}