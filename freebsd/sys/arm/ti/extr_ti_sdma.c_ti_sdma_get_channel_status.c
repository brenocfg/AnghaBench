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
typedef  int /*<<< orphan*/  uint32_t ;
struct ti_sdma_softc {int sc_active_channels; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA4_CSR (unsigned int) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  TI_SDMA_LOCK (struct ti_sdma_softc*) ; 
 int /*<<< orphan*/  TI_SDMA_UNLOCK (struct ti_sdma_softc*) ; 
 int /*<<< orphan*/  ti_sdma_read_4 (struct ti_sdma_softc*,int /*<<< orphan*/ ) ; 
 struct ti_sdma_softc* ti_sdma_sc ; 

int
ti_sdma_get_channel_status(unsigned int ch, uint32_t *status)
{
	struct ti_sdma_softc *sc = ti_sdma_sc;
	uint32_t csr;

	/* Sanity check */
	if (sc == NULL)
		return (ENOMEM);

	TI_SDMA_LOCK(sc);

	if ((sc->sc_active_channels & (1 << ch)) == 0) {
		TI_SDMA_UNLOCK(sc);
		return (EINVAL);
	}

	TI_SDMA_UNLOCK(sc);

	csr = ti_sdma_read_4(sc, DMA4_CSR(ch));

	if (status != NULL)
		*status = csr;

	return (0);
}