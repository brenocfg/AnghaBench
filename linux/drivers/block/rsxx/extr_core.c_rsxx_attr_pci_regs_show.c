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
struct seq_file {struct rsxx_cardinfo* private; } ;
struct rsxx_cardinfo {scalar_t__ regmap; } ;

/* Variables and functions */
 scalar_t__ CREG_ADD ; 
 scalar_t__ CREG_CMD ; 
 scalar_t__ CREG_CNT ; 
 scalar_t__ CREG_DATA0 ; 
 scalar_t__ CREG_DATA1 ; 
 scalar_t__ CREG_DATA2 ; 
 scalar_t__ CREG_DATA3 ; 
 scalar_t__ CREG_DATA4 ; 
 scalar_t__ CREG_DATA5 ; 
 scalar_t__ CREG_DATA6 ; 
 scalar_t__ CREG_DATA7 ; 
 scalar_t__ CREG_STAT ; 
 scalar_t__ HWID ; 
 scalar_t__ HW_ERROR ; 
 scalar_t__ IER ; 
 scalar_t__ INTR_COAL ; 
 scalar_t__ IPR ; 
 scalar_t__ PCI_DEBUG0 ; 
 scalar_t__ PCI_DEBUG1 ; 
 scalar_t__ PCI_DEBUG2 ; 
 scalar_t__ PCI_DEBUG3 ; 
 scalar_t__ PCI_DEBUG4 ; 
 scalar_t__ PCI_DEBUG5 ; 
 scalar_t__ PCI_DEBUG6 ; 
 scalar_t__ PCI_DEBUG7 ; 
 scalar_t__ PCI_RECONFIG ; 
 scalar_t__ SCRATCH ; 
 int /*<<< orphan*/  ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rsxx_attr_pci_regs_show(struct seq_file *m, void *p)
{
	struct rsxx_cardinfo *card = m->private;

	seq_printf(m, "HWID		0x%08x\n",
					ioread32(card->regmap + HWID));
	seq_printf(m, "SCRATCH		0x%08x\n",
					ioread32(card->regmap + SCRATCH));
	seq_printf(m, "IER		0x%08x\n",
					ioread32(card->regmap + IER));
	seq_printf(m, "IPR		0x%08x\n",
					ioread32(card->regmap + IPR));
	seq_printf(m, "CREG_CMD		0x%08x\n",
					ioread32(card->regmap + CREG_CMD));
	seq_printf(m, "CREG_ADD		0x%08x\n",
					ioread32(card->regmap + CREG_ADD));
	seq_printf(m, "CREG_CNT		0x%08x\n",
					ioread32(card->regmap + CREG_CNT));
	seq_printf(m, "CREG_STAT	0x%08x\n",
					ioread32(card->regmap + CREG_STAT));
	seq_printf(m, "CREG_DATA0	0x%08x\n",
					ioread32(card->regmap + CREG_DATA0));
	seq_printf(m, "CREG_DATA1	0x%08x\n",
					ioread32(card->regmap + CREG_DATA1));
	seq_printf(m, "CREG_DATA2	0x%08x\n",
					ioread32(card->regmap + CREG_DATA2));
	seq_printf(m, "CREG_DATA3	0x%08x\n",
					ioread32(card->regmap + CREG_DATA3));
	seq_printf(m, "CREG_DATA4	0x%08x\n",
					ioread32(card->regmap + CREG_DATA4));
	seq_printf(m, "CREG_DATA5	0x%08x\n",
					ioread32(card->regmap + CREG_DATA5));
	seq_printf(m, "CREG_DATA6	0x%08x\n",
					ioread32(card->regmap + CREG_DATA6));
	seq_printf(m, "CREG_DATA7	0x%08x\n",
					ioread32(card->regmap + CREG_DATA7));
	seq_printf(m, "INTR_COAL	0x%08x\n",
					ioread32(card->regmap + INTR_COAL));
	seq_printf(m, "HW_ERROR		0x%08x\n",
					ioread32(card->regmap + HW_ERROR));
	seq_printf(m, "DEBUG0		0x%08x\n",
					ioread32(card->regmap + PCI_DEBUG0));
	seq_printf(m, "DEBUG1		0x%08x\n",
					ioread32(card->regmap + PCI_DEBUG1));
	seq_printf(m, "DEBUG2		0x%08x\n",
					ioread32(card->regmap + PCI_DEBUG2));
	seq_printf(m, "DEBUG3		0x%08x\n",
					ioread32(card->regmap + PCI_DEBUG3));
	seq_printf(m, "DEBUG4		0x%08x\n",
					ioread32(card->regmap + PCI_DEBUG4));
	seq_printf(m, "DEBUG5		0x%08x\n",
					ioread32(card->regmap + PCI_DEBUG5));
	seq_printf(m, "DEBUG6		0x%08x\n",
					ioread32(card->regmap + PCI_DEBUG6));
	seq_printf(m, "DEBUG7		0x%08x\n",
					ioread32(card->regmap + PCI_DEBUG7));
	seq_printf(m, "RECONFIG		0x%08x\n",
					ioread32(card->regmap + PCI_RECONFIG));

	return 0;
}