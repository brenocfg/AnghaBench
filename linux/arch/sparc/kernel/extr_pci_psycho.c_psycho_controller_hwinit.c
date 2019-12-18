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
typedef  int u64 ;
struct pci_pbm_info {scalar_t__ controller_regs; } ;

/* Variables and functions */
 scalar_t__ PSYCHO_IRQ_RETRY ; 
 scalar_t__ PSYCHO_PCIA_CTRL ; 
 scalar_t__ PSYCHO_PCIA_DIAG ; 
 scalar_t__ PSYCHO_PCIB_CTRL ; 
 scalar_t__ PSYCHO_PCIB_DIAG ; 
 int PSYCHO_PCICTRL_AEN ; 
 int PSYCHO_PCIDIAG_DDWSYNC ; 
 int upa_readq (scalar_t__) ; 
 int /*<<< orphan*/  upa_writeq (int,scalar_t__) ; 

__attribute__((used)) static void psycho_controller_hwinit(struct pci_pbm_info *pbm)
{
	u64 tmp;

	upa_writeq(5, pbm->controller_regs + PSYCHO_IRQ_RETRY);

	/* Enable arbiter for all PCI slots. */
	tmp = upa_readq(pbm->controller_regs + PSYCHO_PCIA_CTRL);
	tmp |= PSYCHO_PCICTRL_AEN;
	upa_writeq(tmp, pbm->controller_regs + PSYCHO_PCIA_CTRL);

	tmp = upa_readq(pbm->controller_regs + PSYCHO_PCIB_CTRL);
	tmp |= PSYCHO_PCICTRL_AEN;
	upa_writeq(tmp, pbm->controller_regs + PSYCHO_PCIB_CTRL);

	/* Disable DMA write / PIO read synchronization on
	 * both PCI bus segments.
	 * [ U2P Erratum 1243770, STP2223BGA data sheet ]
	 */
	tmp = upa_readq(pbm->controller_regs + PSYCHO_PCIA_DIAG);
	tmp |= PSYCHO_PCIDIAG_DDWSYNC;
	upa_writeq(tmp, pbm->controller_regs + PSYCHO_PCIA_DIAG);

	tmp = upa_readq(pbm->controller_regs + PSYCHO_PCIB_DIAG);
	tmp |= PSYCHO_PCIDIAG_DDWSYNC;
	upa_writeq(tmp, pbm->controller_regs + PSYCHO_PCIB_DIAG);
}