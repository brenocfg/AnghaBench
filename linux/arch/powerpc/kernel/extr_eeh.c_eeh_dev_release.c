#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pci_dev {int dummy; } ;
struct eeh_dev {TYPE_1__* pe; } ;
struct TYPE_3__ {int /*<<< orphan*/  pass_dev_cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ atomic_dec_if_positive (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eeh_dev_mutex ; 
 int /*<<< orphan*/  eeh_pe_change_owner (TYPE_1__*) ; 
 int /*<<< orphan*/  eeh_pe_passed (TYPE_1__*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct eeh_dev* pci_dev_to_eeh_dev (struct pci_dev*) ; 

void eeh_dev_release(struct pci_dev *pdev)
{
	struct eeh_dev *edev;

	mutex_lock(&eeh_dev_mutex);

	/* No PCI device ? */
	if (!pdev)
		goto out;

	/* No EEH device ? */
	edev = pci_dev_to_eeh_dev(pdev);
	if (!edev || !edev->pe || !eeh_pe_passed(edev->pe))
		goto out;

	/* Decrease PE's pass through count */
	WARN_ON(atomic_dec_if_positive(&edev->pe->pass_dev_cnt) < 0);
	eeh_pe_change_owner(edev->pe);
out:
	mutex_unlock(&eeh_dev_mutex);
}