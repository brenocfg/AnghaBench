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
struct pci_devinst {struct hda_softc* pi_arg; } ;
struct hda_softc {struct pci_devinst* pci_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDA_INTEL_82801G ; 
 int /*<<< orphan*/  HDA_LAST_OFFSET ; 
 int /*<<< orphan*/  INTEL_VENDORID ; 
 int /*<<< orphan*/  PCIBAR_MEM32 ; 
 int PCIC_MULTIMEDIA ; 
 int /*<<< orphan*/  PCIR_CLASS ; 
 int /*<<< orphan*/  PCIR_DEVICE ; 
 int /*<<< orphan*/  PCIR_HDCTL ; 
 int /*<<< orphan*/  PCIR_SUBCLASS ; 
 int /*<<< orphan*/  PCIR_VENDOR ; 
 int PCIS_MULTIMEDIA_HDA ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 struct hda_softc* hda_init (char*) ; 
 int /*<<< orphan*/  pci_emul_alloc_bar (struct pci_devinst*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_lintr_request (struct pci_devinst*) ; 
 int /*<<< orphan*/  pci_set_cfgdata16 (struct pci_devinst*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_cfgdata8 (struct pci_devinst*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
pci_hda_init(struct vmctx *ctx, struct pci_devinst *pi, char *opts)
{
	struct hda_softc *sc = NULL;

	assert(ctx != NULL);
	assert(pi != NULL);

	pci_set_cfgdata16(pi, PCIR_VENDOR, INTEL_VENDORID);
	pci_set_cfgdata16(pi, PCIR_DEVICE, HDA_INTEL_82801G);

	pci_set_cfgdata8(pi, PCIR_SUBCLASS, PCIS_MULTIMEDIA_HDA);
	pci_set_cfgdata8(pi, PCIR_CLASS, PCIC_MULTIMEDIA);

	/* select the Intel HDA mode */
	pci_set_cfgdata8(pi, PCIR_HDCTL, 0x01);

	/* allocate one BAR register for the Memory address offsets */
	pci_emul_alloc_bar(pi, 0, PCIBAR_MEM32, HDA_LAST_OFFSET);

	/* allocate an IRQ pin for our slot */
	pci_lintr_request(pi);

	sc = hda_init(opts);
	if (!sc)
		return (-1);

	sc->pci_dev = pi;
	pi->pi_arg = sc;

	return (0);
}