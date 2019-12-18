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
struct zpci_dev {int /*<<< orphan*/  fh; int /*<<< orphan*/  fid; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLP_SET_DISABLE_PCI_FN ; 
 int clp_set_pci_fn (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zdev_enabled (struct zpci_dev*) ; 
 int /*<<< orphan*/  zpci_dbg (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int clp_disable_fh(struct zpci_dev *zdev)
{
	u32 fh = zdev->fh;
	int rc;

	if (!zdev_enabled(zdev))
		return 0;

	rc = clp_set_pci_fn(&fh, 0, CLP_SET_DISABLE_PCI_FN);
	zpci_dbg(3, "dis fid:%x, fh:%x, rc:%d\n", zdev->fid, fh, rc);
	if (!rc)
		zdev->fh = fh;

	return rc;
}