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
typedef  int uint32_t ;
struct pci_devinst {int dummy; } ;
struct hda_softc {int lintr; struct pci_devinst* pci_dev; } ;

/* Variables and functions */
 int HDAC_INTCTL ; 
 int HDAC_INTCTL_GIE ; 
 int /*<<< orphan*/  HDAC_INTSTS ; 
 int HDAC_INTSTS_CIS ; 
 int HDAC_INTSTS_GIS ; 
 int HDAC_RIRBSTS ; 
 int HDAC_RIRBSTS_RINTFL ; 
 int HDAC_RIRBSTS_RIRBOIS ; 
 int HDAC_SDSTS ; 
 int HDAC_SDSTS_BCIS ; 
 int HDAC_STATESTS ; 
 int HDAC_WAKEEN ; 
 int HDA_IOSS_NO ; 
 int hda_get_offset_stream (int) ; 
 int hda_get_reg_by_offset (struct hda_softc*,int) ; 
 int /*<<< orphan*/  hda_set_reg_by_offset (struct hda_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_lintr_assert (struct pci_devinst*) ; 
 int /*<<< orphan*/  pci_lintr_deassert (struct pci_devinst*) ; 

__attribute__((used)) static void
hda_update_intr(struct hda_softc *sc)
{
	struct pci_devinst *pi = sc->pci_dev;
	uint32_t intctl = hda_get_reg_by_offset(sc, HDAC_INTCTL);
	uint32_t intsts = 0;
	uint32_t sdsts = 0;
	uint32_t rirbsts = 0;
	uint32_t wakeen = 0;
	uint32_t statests = 0;
	uint32_t off = 0;
	int i;

	/* update the CIS bits */
	rirbsts = hda_get_reg_by_offset(sc, HDAC_RIRBSTS);
	if (rirbsts & (HDAC_RIRBSTS_RINTFL | HDAC_RIRBSTS_RIRBOIS))
		intsts |= HDAC_INTSTS_CIS;

	wakeen = hda_get_reg_by_offset(sc, HDAC_WAKEEN);
	statests = hda_get_reg_by_offset(sc, HDAC_STATESTS);
	if (statests & wakeen)
		intsts |= HDAC_INTSTS_CIS;

	/* update the SIS bits */
	for (i = 0; i < HDA_IOSS_NO; i++) {
		off = hda_get_offset_stream(i);
		sdsts = hda_get_reg_by_offset(sc, off + HDAC_SDSTS);
		if (sdsts & HDAC_SDSTS_BCIS)
			intsts |= (1 << i);
	}

	/* update the GIS bit */
	if (intsts)
		intsts |= HDAC_INTSTS_GIS;

	hda_set_reg_by_offset(sc, HDAC_INTSTS, intsts);

	if ((intctl & HDAC_INTCTL_GIE) && ((intsts &			\
		~HDAC_INTSTS_GIS) & intctl)) {
		if (!sc->lintr) {
			pci_lintr_assert(pi);
			sc->lintr = 1;
		}
	} else {
		if (sc->lintr) {
			pci_lintr_deassert(pi);
			sc->lintr = 0;
		}
	}
}