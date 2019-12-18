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
typedef  int /*<<< orphan*/  u64 ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct cptvf_wqe_info {TYPE_1__* vq_wqe; } ;
struct cpt_vf {int nr_queues; struct cptvf_wqe_info* wqe_info; struct pci_dev* pdev; } ;
struct TYPE_2__ {int qno; struct cpt_vf* cptvf; int /*<<< orphan*/  twork; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int) ; 
 struct cptvf_wqe_info* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vq_work_handler ; 

__attribute__((used)) static int init_worker_threads(struct cpt_vf *cptvf)
{
	struct pci_dev *pdev = cptvf->pdev;
	struct cptvf_wqe_info *cwqe_info;
	int i;

	cwqe_info = kzalloc(sizeof(*cwqe_info), GFP_KERNEL);
	if (!cwqe_info)
		return -ENOMEM;

	if (cptvf->nr_queues) {
		dev_info(&pdev->dev, "Creating VQ worker threads (%d)\n",
			 cptvf->nr_queues);
	}

	for (i = 0; i < cptvf->nr_queues; i++) {
		tasklet_init(&cwqe_info->vq_wqe[i].twork, vq_work_handler,
			     (u64)cwqe_info);
		cwqe_info->vq_wqe[i].qno = i;
		cwqe_info->vq_wqe[i].cptvf = cptvf;
	}

	cptvf->wqe_info = cwqe_info;

	return 0;
}