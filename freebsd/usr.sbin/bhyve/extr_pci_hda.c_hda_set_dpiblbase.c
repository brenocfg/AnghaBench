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
typedef  int uint64_t ;
typedef  int uint32_t ;
struct hda_softc {int /*<<< orphan*/ * dma_pib_vaddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,...) ; 
 int HDAC_DPIBUBASE ; 
 int HDAC_DPLBASE_DPLBASE_DMAPBE ; 
 int HDAC_DPLBASE_DPLBASE_MASK ; 
 int HDA_DMA_PIB_ENTRY_LEN ; 
 int HDA_IOSS_NO ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * hda_dma_get_vaddr (struct hda_softc*,int,int) ; 
 int hda_get_reg_by_offset (struct hda_softc*,int) ; 

__attribute__((used)) static void
hda_set_dpiblbase(struct hda_softc *sc, uint32_t offset, uint32_t old)
{
	uint32_t value = hda_get_reg_by_offset(sc, offset);
	uint64_t dpiblbase = 0;
	uint64_t dpibubase = 0;
	uint64_t dpibpaddr = 0;

	if ((value & HDAC_DPLBASE_DPLBASE_DMAPBE) != (old &		\
				HDAC_DPLBASE_DPLBASE_DMAPBE)) {
		if (value & HDAC_DPLBASE_DPLBASE_DMAPBE) {
			dpiblbase = value & HDAC_DPLBASE_DPLBASE_MASK;
			dpibubase = hda_get_reg_by_offset(sc, HDAC_DPIBUBASE);

			dpibpaddr = dpiblbase | (dpibubase << 32);
			DPRINTF("DMA Position In Buffer dma_paddr: %p\n",
			    (void *)dpibpaddr);

			sc->dma_pib_vaddr = hda_dma_get_vaddr(sc, dpibpaddr,
					HDA_DMA_PIB_ENTRY_LEN * HDA_IOSS_NO);
			if (!sc->dma_pib_vaddr) {
				DPRINTF("Fail to get the guest \
					 virtual address\n");
				assert(0);
			}
		} else {
			DPRINTF("DMA Position In Buffer Reset\n");
			sc->dma_pib_vaddr = NULL;
		}
	}
}