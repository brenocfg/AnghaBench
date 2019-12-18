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
struct pci_device_id {int dummy; } ;
struct pci_dev {scalar_t__ device; int /*<<< orphan*/  dev; } ;
struct hisi_qm {int ver; scalar_t__ fun_type; int use_dma_api; void* qp_num; void* qp_base; int /*<<< orphan*/  dev_name; int /*<<< orphan*/  sqe_size; struct pci_dev* pdev; } ;
struct hisi_zip {struct hisi_qm qm; } ;
typedef  enum qm_hw_ver { ____Placeholder_qm_hw_ver } qm_hw_ver ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* HZIP_PF_DEF_Q_BASE ; 
 void* HZIP_PF_DEF_Q_NUM ; 
 void* HZIP_QUEUE_NUM_V1 ; 
 int /*<<< orphan*/  HZIP_SQE_SIZE ; 
 scalar_t__ PCI_DEVICE_ID_ZIP_PF ; 
 scalar_t__ QM_HW_PF ; 
 int QM_HW_UNKNOWN ; 
 scalar_t__ QM_HW_V1 ; 
 scalar_t__ QM_HW_V2 ; 
 scalar_t__ QM_HW_VF ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 struct hisi_zip* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int hisi_qm_get_hw_version (struct pci_dev*) ; 
 int /*<<< orphan*/  hisi_qm_get_vft (struct hisi_qm*,void**,void**) ; 
 int hisi_qm_init (struct hisi_qm*) ; 
 int hisi_qm_start (struct hisi_qm*) ; 
 int /*<<< orphan*/  hisi_qm_uninit (struct hisi_qm*) ; 
 int /*<<< orphan*/  hisi_zip_add_to_list (struct hisi_zip*) ; 
 int hisi_zip_debugfs_init (struct hisi_zip*) ; 
 int /*<<< orphan*/  hisi_zip_name ; 
 int hisi_zip_pf_probe_init (struct hisi_zip*) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct hisi_zip*) ; 
 void* pf_q_num ; 
 int uacce_mode ; 

__attribute__((used)) static int hisi_zip_probe(struct pci_dev *pdev, const struct pci_device_id *id)
{
	struct hisi_zip *hisi_zip;
	enum qm_hw_ver rev_id;
	struct hisi_qm *qm;
	int ret;

	rev_id = hisi_qm_get_hw_version(pdev);
	if (rev_id == QM_HW_UNKNOWN)
		return -EINVAL;

	hisi_zip = devm_kzalloc(&pdev->dev, sizeof(*hisi_zip), GFP_KERNEL);
	if (!hisi_zip)
		return -ENOMEM;
	pci_set_drvdata(pdev, hisi_zip);

	qm = &hisi_zip->qm;
	qm->pdev = pdev;
	qm->ver = rev_id;

	qm->sqe_size = HZIP_SQE_SIZE;
	qm->dev_name = hisi_zip_name;
	qm->fun_type = (pdev->device == PCI_DEVICE_ID_ZIP_PF) ? QM_HW_PF :
								QM_HW_VF;
	switch (uacce_mode) {
	case 0:
		qm->use_dma_api = true;
		break;
	case 1:
		qm->use_dma_api = false;
		break;
	case 2:
		qm->use_dma_api = true;
		break;
	default:
		return -EINVAL;
	}

	ret = hisi_qm_init(qm);
	if (ret) {
		dev_err(&pdev->dev, "Failed to init qm!\n");
		return ret;
	}

	if (qm->fun_type == QM_HW_PF) {
		ret = hisi_zip_pf_probe_init(hisi_zip);
		if (ret)
			return ret;

		qm->qp_base = HZIP_PF_DEF_Q_BASE;
		qm->qp_num = pf_q_num;
	} else if (qm->fun_type == QM_HW_VF) {
		/*
		 * have no way to get qm configure in VM in v1 hardware,
		 * so currently force PF to uses HZIP_PF_DEF_Q_NUM, and force
		 * to trigger only one VF in v1 hardware.
		 *
		 * v2 hardware has no such problem.
		 */
		if (qm->ver == QM_HW_V1) {
			qm->qp_base = HZIP_PF_DEF_Q_NUM;
			qm->qp_num = HZIP_QUEUE_NUM_V1 - HZIP_PF_DEF_Q_NUM;
		} else if (qm->ver == QM_HW_V2)
			/* v2 starts to support get vft by mailbox */
			hisi_qm_get_vft(qm, &qm->qp_base, &qm->qp_num);
	}

	ret = hisi_qm_start(qm);
	if (ret)
		goto err_qm_uninit;

	ret = hisi_zip_debugfs_init(hisi_zip);
	if (ret)
		dev_err(&pdev->dev, "Failed to init debugfs (%d)!\n", ret);

	hisi_zip_add_to_list(hisi_zip);

	return 0;

err_qm_uninit:
	hisi_qm_uninit(qm);
	return ret;
}