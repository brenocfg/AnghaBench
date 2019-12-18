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
struct pci_dev {int dummy; } ;
struct mem_ctl_info {int /*<<< orphan*/  pdev; } ;
struct i3000_error_info {int errsts; int errsts2; int /*<<< orphan*/  derrsyn; int /*<<< orphan*/  deap; int /*<<< orphan*/  edeap; } ;

/* Variables and functions */
 int /*<<< orphan*/  I3000_DEAP ; 
 int /*<<< orphan*/  I3000_DERRSYN ; 
 int /*<<< orphan*/  I3000_EDEAP ; 
 int /*<<< orphan*/  I3000_ERRSTS ; 
 int I3000_ERRSTS_BITS ; 
 int /*<<< orphan*/  pci_read_config_byte (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_read_config_word (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_write_bits16 (struct pci_dev*,int /*<<< orphan*/ ,int,int) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void i3000_get_error_info(struct mem_ctl_info *mci,
				 struct i3000_error_info *info)
{
	struct pci_dev *pdev;

	pdev = to_pci_dev(mci->pdev);

	/*
	 * This is a mess because there is no atomic way to read all the
	 * registers at once and the registers can transition from CE being
	 * overwritten by UE.
	 */
	pci_read_config_word(pdev, I3000_ERRSTS, &info->errsts);
	if (!(info->errsts & I3000_ERRSTS_BITS))
		return;
	pci_read_config_byte(pdev, I3000_EDEAP, &info->edeap);
	pci_read_config_dword(pdev, I3000_DEAP, &info->deap);
	pci_read_config_byte(pdev, I3000_DERRSYN, &info->derrsyn);
	pci_read_config_word(pdev, I3000_ERRSTS, &info->errsts2);

	/*
	 * If the error is the same for both reads then the first set
	 * of reads is valid.  If there is a change then there is a CE
	 * with no info and the second set of reads is valid and
	 * should be UE info.
	 */
	if ((info->errsts ^ info->errsts2) & I3000_ERRSTS_BITS) {
		pci_read_config_byte(pdev, I3000_EDEAP, &info->edeap);
		pci_read_config_dword(pdev, I3000_DEAP, &info->deap);
		pci_read_config_byte(pdev, I3000_DERRSYN, &info->derrsyn);
	}

	/*
	 * Clear any error bits.
	 * (Yes, we really clear bits by writing 1 to them.)
	 */
	pci_write_bits16(pdev, I3000_ERRSTS, I3000_ERRSTS_BITS,
			 I3000_ERRSTS_BITS);
}