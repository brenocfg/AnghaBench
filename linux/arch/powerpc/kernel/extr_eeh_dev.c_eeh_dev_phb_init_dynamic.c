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
struct pci_controller {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  eeh_phb_pe_create (struct pci_controller*) ; 

void eeh_dev_phb_init_dynamic(struct pci_controller *phb)
{
	/* EEH PE for PHB */
	eeh_phb_pe_create(phb);
}