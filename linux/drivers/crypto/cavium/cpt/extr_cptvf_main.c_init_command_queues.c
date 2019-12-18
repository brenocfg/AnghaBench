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
typedef  int /*<<< orphan*/  u32 ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct cpt_vf {int /*<<< orphan*/  nr_queues; int /*<<< orphan*/  cqinfo; struct pci_dev* pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPT_INST_SIZE ; 
 int alloc_command_queues (struct cpt_vf*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int init_command_queues(struct cpt_vf *cptvf, u32 qlen)
{
	struct pci_dev *pdev = cptvf->pdev;
	int ret;

	/* setup AE command queues */
	ret = alloc_command_queues(cptvf, &cptvf->cqinfo, CPT_INST_SIZE,
				   qlen);
	if (ret) {
		dev_err(&pdev->dev, "failed to allocate AE command queues (%u)\n",
			cptvf->nr_queues);
		return ret;
	}

	return ret;
}