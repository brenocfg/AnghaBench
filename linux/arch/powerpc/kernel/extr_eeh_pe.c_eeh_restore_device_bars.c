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
typedef  int u32 ;
struct pci_dn {int dummy; } ;
struct eeh_dev {int* config_space; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* write_config ) (struct pci_dn*,int,int,int) ;int /*<<< orphan*/  (* read_config ) (struct pci_dn*,int,int,int*) ;} ;

/* Variables and functions */
 int PCI_CACHE_LINE_SIZE ; 
 int PCI_COMMAND ; 
 int PCI_COMMAND_PARITY ; 
 int PCI_COMMAND_SERR ; 
 int PCI_LATENCY_TIMER ; 
 int SAVED_BYTE (int) ; 
 struct pci_dn* eeh_dev_to_pdn (struct eeh_dev*) ; 
 TYPE_1__* eeh_ops ; 
 int /*<<< orphan*/  stub1 (struct pci_dn*,int,int,int) ; 
 int /*<<< orphan*/  stub2 (struct pci_dn*,int,int,int) ; 
 int /*<<< orphan*/  stub3 (struct pci_dn*,int,int,int) ; 
 int /*<<< orphan*/  stub4 (struct pci_dn*,int,int,int) ; 
 int /*<<< orphan*/  stub5 (struct pci_dn*,int,int,int) ; 
 int /*<<< orphan*/  stub6 (struct pci_dn*,int,int,int*) ; 
 int /*<<< orphan*/  stub7 (struct pci_dn*,int,int,int) ; 

__attribute__((used)) static void eeh_restore_device_bars(struct eeh_dev *edev)
{
	struct pci_dn *pdn = eeh_dev_to_pdn(edev);
	int i;
	u32 cmd;

	for (i = 4; i < 10; i++)
		eeh_ops->write_config(pdn, i*4, 4, edev->config_space[i]);
	/* 12 == Expansion ROM Address */
	eeh_ops->write_config(pdn, 12*4, 4, edev->config_space[12]);

	eeh_ops->write_config(pdn, PCI_CACHE_LINE_SIZE, 1,
		SAVED_BYTE(PCI_CACHE_LINE_SIZE));
	eeh_ops->write_config(pdn, PCI_LATENCY_TIMER, 1,
		SAVED_BYTE(PCI_LATENCY_TIMER));

	/* max latency, min grant, interrupt pin and line */
	eeh_ops->write_config(pdn, 15*4, 4, edev->config_space[15]);

	/*
	 * Restore PERR & SERR bits, some devices require it,
	 * don't touch the other command bits
	 */
	eeh_ops->read_config(pdn, PCI_COMMAND, 4, &cmd);
	if (edev->config_space[1] & PCI_COMMAND_PARITY)
		cmd |= PCI_COMMAND_PARITY;
	else
		cmd &= ~PCI_COMMAND_PARITY;
	if (edev->config_space[1] & PCI_COMMAND_SERR)
		cmd |= PCI_COMMAND_SERR;
	else
		cmd &= ~PCI_COMMAND_SERR;
	eeh_ops->write_config(pdn, PCI_COMMAND, 4, cmd);
}