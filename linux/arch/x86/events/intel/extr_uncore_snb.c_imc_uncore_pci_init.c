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
struct pci_driver {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 struct pci_driver* imc_uncore_find_dev () ; 
 int /*<<< orphan*/  snb_pci_uncores ; 
 struct pci_driver* uncore_pci_driver ; 
 int /*<<< orphan*/  uncore_pci_uncores ; 

__attribute__((used)) static int imc_uncore_pci_init(void)
{
	struct pci_driver *imc_drv = imc_uncore_find_dev();

	if (!imc_drv)
		return -ENODEV;

	uncore_pci_uncores = snb_pci_uncores;
	uncore_pci_driver = imc_drv;

	return 0;
}