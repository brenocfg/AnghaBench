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
typedef  int uint8_t ;
typedef  scalar_t__ uint32_t ;
struct hda_softc {scalar_t__ dma_pib_vaddr; } ;

/* Variables and functions */
 scalar_t__ HDAC_SDLPIB ; 
 int HDA_DMA_PIB_ENTRY_LEN ; 
 scalar_t__ hda_get_offset_stream (int) ; 
 int /*<<< orphan*/  hda_set_reg_by_offset (struct hda_softc*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void
hda_set_pib(struct hda_softc *sc, uint8_t stream_ind, uint32_t pib)
{
	uint32_t off = hda_get_offset_stream(stream_ind);

	hda_set_reg_by_offset(sc, off + HDAC_SDLPIB, pib);
	/* LPIB Alias */
	hda_set_reg_by_offset(sc, 0x2000 + off + HDAC_SDLPIB, pib);
	if (sc->dma_pib_vaddr)
		*(uint32_t *)(sc->dma_pib_vaddr + stream_ind *	\
				HDA_DMA_PIB_ENTRY_LEN) = pib;
}