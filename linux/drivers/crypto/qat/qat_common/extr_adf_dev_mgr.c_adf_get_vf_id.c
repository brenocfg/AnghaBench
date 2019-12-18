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
struct adf_accel_dev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  devfn; } ;

/* Variables and functions */
 int PCI_FUNC (int /*<<< orphan*/ ) ; 
 int PCI_SLOT (int /*<<< orphan*/ ) ; 
 TYPE_1__* accel_to_pci_dev (struct adf_accel_dev*) ; 

__attribute__((used)) static int adf_get_vf_id(struct adf_accel_dev *vf)
{
	return ((7 * (PCI_SLOT(accel_to_pci_dev(vf)->devfn) - 1)) +
		PCI_FUNC(accel_to_pci_dev(vf)->devfn) +
		(PCI_SLOT(accel_to_pci_dev(vf)->devfn) - 1));
}