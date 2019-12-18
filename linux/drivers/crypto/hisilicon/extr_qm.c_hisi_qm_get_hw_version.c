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
struct pci_dev {int revision; } ;
typedef  enum qm_hw_ver { ____Placeholder_qm_hw_ver } qm_hw_ver ;

/* Variables and functions */
 int QM_HW_UNKNOWN ; 
#define  QM_HW_V1 129 
#define  QM_HW_V2 128 

enum qm_hw_ver hisi_qm_get_hw_version(struct pci_dev *pdev)
{
	switch (pdev->revision) {
	case QM_HW_V1:
	case QM_HW_V2:
		return pdev->revision;
	default:
		return QM_HW_UNKNOWN;
	}
}