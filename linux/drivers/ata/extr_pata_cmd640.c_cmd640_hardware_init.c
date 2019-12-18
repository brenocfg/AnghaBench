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
typedef  int u8 ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int ARTIM23 ; 
 int BRST ; 
 int CMDTIM ; 
 int CNTRL ; 
 int /*<<< orphan*/  pci_read_config_byte (struct pci_dev*,int,int*) ; 
 int /*<<< orphan*/  pci_write_config_byte (struct pci_dev*,int,int) ; 

__attribute__((used)) static void cmd640_hardware_init(struct pci_dev *pdev)
{
	u8 ctrl;

	/* CMD640 detected, commiserations */
	pci_write_config_byte(pdev, 0x5B, 0x00);
	/* PIO0 command cycles */
	pci_write_config_byte(pdev, CMDTIM, 0);
	/* 512 byte bursts (sector) */
	pci_write_config_byte(pdev, BRST, 0x40);
	/*
	 * A reporter a long time ago
	 * Had problems with the data fifo
	 * So don't run the risk
	 * Of putting crap on the disk
	 * For its better just to go slow
	 */
	/* Do channel 0 */
	pci_read_config_byte(pdev, CNTRL, &ctrl);
	pci_write_config_byte(pdev, CNTRL, ctrl | 0xC0);
	/* Ditto for channel 1 */
	pci_read_config_byte(pdev, ARTIM23, &ctrl);
	ctrl |= 0x0C;
	pci_write_config_byte(pdev, ARTIM23, ctrl);
}