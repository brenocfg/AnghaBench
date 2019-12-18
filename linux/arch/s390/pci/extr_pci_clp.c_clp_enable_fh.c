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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct zpci_dev {int /*<<< orphan*/  fid; int /*<<< orphan*/  fh; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLP_SET_ENABLE_MIO ; 
 int /*<<< orphan*/  CLP_SET_ENABLE_PCI_FN ; 
 int /*<<< orphan*/  clp_disable_fh (struct zpci_dev*) ; 
 int clp_set_pci_fn (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zpci_dbg (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ zpci_use_mio (struct zpci_dev*) ; 

int clp_enable_fh(struct zpci_dev *zdev, u8 nr_dma_as)
{
	u32 fh = zdev->fh;
	int rc;

	rc = clp_set_pci_fn(&fh, nr_dma_as, CLP_SET_ENABLE_PCI_FN);
	zpci_dbg(3, "ena fid:%x, fh:%x, rc:%d\n", zdev->fid, fh, rc);
	if (rc)
		goto out;

	zdev->fh = fh;
	if (zpci_use_mio(zdev)) {
		rc = clp_set_pci_fn(&fh, nr_dma_as, CLP_SET_ENABLE_MIO);
		zpci_dbg(3, "ena mio fid:%x, fh:%x, rc:%d\n", zdev->fid, fh, rc);
		if (rc)
			clp_disable_fh(zdev);
	}
out:
	return rc;
}