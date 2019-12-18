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
typedef  int u16 ;
struct idt77252_dev {int /*<<< orphan*/  name; int /*<<< orphan*/  pcidev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPRINTK (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCI_COMMAND ; 
 int PCI_COMMAND_IO ; 
 int PCI_COMMAND_MASTER ; 
 int PCI_COMMAND_MEMORY ; 
 int /*<<< orphan*/  SAR_CFG_SWRST ; 
 int /*<<< orphan*/  SAR_REG_CFG ; 
 int /*<<< orphan*/  XPRINTK (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  deinit_card (struct idt77252_dev*) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 scalar_t__ pci_read_config_word (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ pci_write_config_word (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int idt77252_preset(struct idt77252_dev *card)
{
	u16 pci_command;

/*****************************************************************/
/*   P C I   C O N F I G U R A T I O N                           */
/*****************************************************************/

	XPRINTK("%s: Enable PCI master and memory access for SAR.\n",
		card->name);
	if (pci_read_config_word(card->pcidev, PCI_COMMAND, &pci_command)) {
		printk("%s: can't read PCI_COMMAND.\n", card->name);
		deinit_card(card);
		return -1;
	}
	if (!(pci_command & PCI_COMMAND_IO)) {
		printk("%s: PCI_COMMAND: %04x (???)\n",
		       card->name, pci_command);
		deinit_card(card);
		return (-1);
	}
	pci_command |= (PCI_COMMAND_MEMORY | PCI_COMMAND_MASTER);
	if (pci_write_config_word(card->pcidev, PCI_COMMAND, pci_command)) {
		printk("%s: can't write PCI_COMMAND.\n", card->name);
		deinit_card(card);
		return -1;
	}
/*****************************************************************/
/*   G E N E R I C   R E S E T                                   */
/*****************************************************************/

	/* Software reset */
	writel(SAR_CFG_SWRST, SAR_REG_CFG);
	mdelay(1);
	writel(0, SAR_REG_CFG);

	IPRINTK("%s: Software resetted.\n", card->name);
	return 0;
}