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
struct vmctx {int dummy; } ;
struct pci_emul_dsoftc {int dummy; } ;
struct pci_devinst {struct pci_emul_dsoftc* pi_arg; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIOSZ ; 
 int /*<<< orphan*/  DMEMSZ ; 
 int /*<<< orphan*/  PCIBAR_IO ; 
 int /*<<< orphan*/  PCIBAR_MEM32 ; 
 int /*<<< orphan*/  PCIR_CLASS ; 
 int /*<<< orphan*/  PCIR_DEVICE ; 
 int /*<<< orphan*/  PCIR_VENDOR ; 
 int /*<<< orphan*/  PCI_EMUL_MSI_MSGS ; 
 int /*<<< orphan*/  assert (int) ; 
 struct pci_emul_dsoftc* calloc (int,int) ; 
 int pci_emul_add_msicap (struct pci_devinst*,int /*<<< orphan*/ ) ; 
 int pci_emul_alloc_bar (struct pci_devinst*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_cfgdata16 (struct pci_devinst*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_set_cfgdata8 (struct pci_devinst*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
pci_emul_dinit(struct vmctx *ctx, struct pci_devinst *pi, char *opts)
{
	int error;
	struct pci_emul_dsoftc *sc;

	sc = calloc(1, sizeof(struct pci_emul_dsoftc));

	pi->pi_arg = sc;

	pci_set_cfgdata16(pi, PCIR_DEVICE, 0x0001);
	pci_set_cfgdata16(pi, PCIR_VENDOR, 0x10DD);
	pci_set_cfgdata8(pi, PCIR_CLASS, 0x02);

	error = pci_emul_add_msicap(pi, PCI_EMUL_MSI_MSGS);
	assert(error == 0);

	error = pci_emul_alloc_bar(pi, 0, PCIBAR_IO, DIOSZ);
	assert(error == 0);

	error = pci_emul_alloc_bar(pi, 1, PCIBAR_MEM32, DMEMSZ);
	assert(error == 0);

	error = pci_emul_alloc_bar(pi, 2, PCIBAR_MEM32, DMEMSZ);
	assert(error == 0);

	return (0);
}