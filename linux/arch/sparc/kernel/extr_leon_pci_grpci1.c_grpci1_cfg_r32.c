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
struct grpci1_priv {unsigned int pci_conf; TYPE_1__* regs; } ;
struct TYPE_2__ {int /*<<< orphan*/  stat_cmd; int /*<<< orphan*/  cfg_stat; } ;

/* Variables and functions */
 int CFGSTAT_CTO ; 
 int EINVAL ; 
 int LEON3_BYPASS_LOAD_PA (int*) ; 
 int /*<<< orphan*/  PCI_COMMAND ; 
 int REGLOAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REGSTORE (int /*<<< orphan*/ ,int) ; 
 unsigned int TGT ; 
 int /*<<< orphan*/  grpci1_cfg_w32 (struct grpci1_priv*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int swab32 (int) ; 

__attribute__((used)) static int grpci1_cfg_r32(struct grpci1_priv *priv, unsigned int bus,
				unsigned int devfn, int where, u32 *val)
{
	u32 *pci_conf, tmp, cfg;

	if (where & 0x3)
		return -EINVAL;

	if (bus == 0) {
		devfn += (0x8 * 6); /* start at AD16=Device0 */
	} else if (bus == TGT) {
		bus = 0;
		devfn = 0; /* special case: bridge controller itself */
	}

	/* Select bus */
	cfg = REGLOAD(priv->regs->cfg_stat);
	REGSTORE(priv->regs->cfg_stat, (cfg & ~(0xf << 23)) | (bus << 23));

	/* do read access */
	pci_conf = (u32 *) (priv->pci_conf | (devfn << 8) | (where & 0xfc));
	tmp = LEON3_BYPASS_LOAD_PA(pci_conf);

	/* check if master abort was received */
	if (REGLOAD(priv->regs->cfg_stat) & CFGSTAT_CTO) {
		*val = 0xffffffff;
		/* Clear Master abort bit in PCI cfg space (is set) */
		tmp = REGLOAD(priv->regs->stat_cmd);
		grpci1_cfg_w32(priv, TGT, 0, PCI_COMMAND, tmp);
	} else {
		/* Bus always little endian (unaffected by byte-swapping) */
		*val = swab32(tmp);
	}

	return 0;
}