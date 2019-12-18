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
struct pci_dev {int dummy; } ;
struct hisi_qm {scalar_t__ fun_type; } ;
struct hisi_zip {TYPE_1__* ctrl; struct hisi_qm qm; } ;
struct TYPE_2__ {scalar_t__ num_vfs; } ;

/* Variables and functions */
 scalar_t__ QM_HW_PF ; 
 int /*<<< orphan*/  hisi_qm_stop (struct hisi_qm*) ; 
 int /*<<< orphan*/  hisi_qm_uninit (struct hisi_qm*) ; 
 int /*<<< orphan*/  hisi_zip_debugfs_exit (struct hisi_zip*) ; 
 int /*<<< orphan*/  hisi_zip_hw_error_set_state (struct hisi_zip*,int) ; 
 int /*<<< orphan*/  hisi_zip_remove_from_list (struct hisi_zip*) ; 
 int /*<<< orphan*/  hisi_zip_sriov_disable (struct pci_dev*) ; 
 struct hisi_zip* pci_get_drvdata (struct pci_dev*) ; 

__attribute__((used)) static void hisi_zip_remove(struct pci_dev *pdev)
{
	struct hisi_zip *hisi_zip = pci_get_drvdata(pdev);
	struct hisi_qm *qm = &hisi_zip->qm;

	if (qm->fun_type == QM_HW_PF && hisi_zip->ctrl->num_vfs != 0)
		hisi_zip_sriov_disable(pdev);

	hisi_zip_debugfs_exit(hisi_zip);
	hisi_qm_stop(qm);

	if (qm->fun_type == QM_HW_PF)
		hisi_zip_hw_error_set_state(hisi_zip, false);

	hisi_qm_uninit(qm);
	hisi_zip_remove_from_list(hisi_zip);
}