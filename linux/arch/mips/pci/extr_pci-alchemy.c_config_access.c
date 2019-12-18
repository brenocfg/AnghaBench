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
typedef  unsigned long u32 ;
struct pci_bus {int number; struct alchemy_pci_context* sysdata; } ;
struct alchemy_pci_context {scalar_t__ (* board_pci_idsel ) (unsigned int,int) ;unsigned long last_elo0; unsigned long last_elo1; scalar_t__ regs; TYPE_1__* pci_cfg_vm; int /*<<< orphan*/  wired_entry; } ;
struct TYPE_2__ {scalar_t__ addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,unsigned int,unsigned long,...) ; 
 unsigned long PAGE_MASK ; 
 int PCIBIOS_SUCCESSFUL ; 
 unsigned char PCI_ACCESS_WRITE ; 
 unsigned int PCI_FUNC (unsigned int) ; 
 scalar_t__ PCI_REG_STATCMD ; 
 unsigned int PCI_SLOT (unsigned int) ; 
 unsigned long PCI_STATCMD_STATUS (int) ; 
 int /*<<< orphan*/  PM_4K ; 
 int __raw_readl (scalar_t__) ; 
 int /*<<< orphan*/  __raw_writel (unsigned long,scalar_t__) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  mod_wired_entry (int /*<<< orphan*/ ,unsigned long,unsigned long,unsigned long,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (unsigned int,int) ; 
 scalar_t__ stub2 (unsigned int,int) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static int config_access(unsigned char access_type, struct pci_bus *bus,
			 unsigned int dev_fn, unsigned char where, u32 *data)
{
	struct alchemy_pci_context *ctx = bus->sysdata;
	unsigned int device = PCI_SLOT(dev_fn);
	unsigned int function = PCI_FUNC(dev_fn);
	unsigned long offset, status, cfg_base, flags, entryLo0, entryLo1, r;
	int error = PCIBIOS_SUCCESSFUL;

	if (device > 19) {
		*data = 0xffffffff;
		return -1;
	}

	local_irq_save(flags);
	r = __raw_readl(ctx->regs + PCI_REG_STATCMD) & 0x0000ffff;
	r |= PCI_STATCMD_STATUS(0x2000);
	__raw_writel(r, ctx->regs + PCI_REG_STATCMD);
	wmb();

	/* Allow board vendors to implement their own off-chip IDSEL.
	 * If it doesn't succeed, may as well bail out at this point.
	 */
	if (ctx->board_pci_idsel(device, 1) == 0) {
		*data = 0xffffffff;
		local_irq_restore(flags);
		return -1;
	}

	/* Setup the config window */
	if (bus->number == 0)
		cfg_base = (1 << device) << 11;
	else
		cfg_base = 0x80000000 | (bus->number << 16) | (device << 11);

	/* Setup the lower bits of the 36-bit address */
	offset = (function << 8) | (where & ~0x3);
	/* Pick up any address that falls below the page mask */
	offset |= cfg_base & ~PAGE_MASK;

	/* Page boundary */
	cfg_base = cfg_base & PAGE_MASK;

	/* To improve performance, if the current device is the same as
	 * the last device accessed, we don't touch the TLB.
	 */
	entryLo0 = (6 << 26) | (cfg_base >> 6) | (2 << 3) | 7;
	entryLo1 = (6 << 26) | (cfg_base >> 6) | (0x1000 >> 6) | (2 << 3) | 7;
	if ((entryLo0 != ctx->last_elo0) || (entryLo1 != ctx->last_elo1)) {
		mod_wired_entry(ctx->wired_entry, entryLo0, entryLo1,
				(unsigned long)ctx->pci_cfg_vm->addr, PM_4K);
		ctx->last_elo0 = entryLo0;
		ctx->last_elo1 = entryLo1;
	}

	if (access_type == PCI_ACCESS_WRITE)
		__raw_writel(*data, ctx->pci_cfg_vm->addr + offset);
	else
		*data = __raw_readl(ctx->pci_cfg_vm->addr + offset);
	wmb();

	DBG("alchemy-pci: cfg access %d bus %u dev %u at %x dat %x conf %lx\n",
	    access_type, bus->number, device, where, *data, offset);

	/* check for errors, master abort */
	status = __raw_readl(ctx->regs + PCI_REG_STATCMD);
	if (status & (1 << 29)) {
		*data = 0xffffffff;
		error = -1;
		DBG("alchemy-pci: master abort on cfg access %d bus %d dev %d\n",
		    access_type, bus->number, device);
	} else if ((status >> 28) & 0xf) {
		DBG("alchemy-pci: PCI ERR detected: dev %d, status %lx\n",
		    device, (status >> 28) & 0xf);

		/* clear errors */
		__raw_writel(status & 0xf000ffff, ctx->regs + PCI_REG_STATCMD);

		*data = 0xffffffff;
		error = -1;
	}

	/* Take away the IDSEL. */
	(void)ctx->board_pci_idsel(device, 0);

	local_irq_restore(flags);
	return error;
}