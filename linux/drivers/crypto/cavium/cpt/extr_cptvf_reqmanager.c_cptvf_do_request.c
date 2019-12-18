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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct cpt_vf {scalar_t__ vftype; int /*<<< orphan*/  vfid; struct pci_dev* pdev; } ;
struct TYPE_3__ {scalar_t__ se_req; } ;
struct TYPE_4__ {TYPE_1__ s; } ;
struct cpt_request_info {TYPE_2__ ctrl; } ;

/* Variables and functions */
 scalar_t__ AE_TYPES ; 
 int EINVAL ; 
 int ENODEV ; 
 scalar_t__ SE_TYPES ; 
 int /*<<< orphan*/  cpt_device_ready (struct cpt_vf*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int process_request (struct cpt_vf*,struct cpt_request_info*) ; 

int cptvf_do_request(void *vfdev, struct cpt_request_info *req)
{
	struct cpt_vf *cptvf = (struct cpt_vf *)vfdev;
	struct pci_dev *pdev = cptvf->pdev;

	if (!cpt_device_ready(cptvf)) {
		dev_err(&pdev->dev, "CPT Device is not ready");
		return -ENODEV;
	}

	if ((cptvf->vftype == SE_TYPES) && (!req->ctrl.s.se_req)) {
		dev_err(&pdev->dev, "CPTVF-%d of SE TYPE got AE request",
			cptvf->vfid);
		return -EINVAL;
	} else if ((cptvf->vftype == AE_TYPES) && (req->ctrl.s.se_req)) {
		dev_err(&pdev->dev, "CPTVF-%d of AE TYPE got SE request",
			cptvf->vfid);
		return -EINVAL;
	}

	return process_request(cptvf, req);
}