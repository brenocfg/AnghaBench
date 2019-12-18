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
typedef  int /*<<< orphan*/  device_t ;
typedef  int boolean_t ;

/* Variables and functions */
 scalar_t__ PCI_REVID_PASS2 ; 
 scalar_t__ pci_get_revid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline boolean_t
pass1_silicon(device_t dev)
{

	/* Check if the chip revision is < Pass2 */
	return (pci_get_revid(dev) < PCI_REVID_PASS2);
}