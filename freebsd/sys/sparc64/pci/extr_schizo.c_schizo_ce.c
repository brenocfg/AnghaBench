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
struct schizo_softc {int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/  sc_dev; int /*<<< orphan*/  sc_stats_dma_ce; } ;

/* Variables and functions */
 int FILTER_HANDLED ; 
 int SCHIZO_CTRL_READ_8 (struct schizo_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCHIZO_CTRL_WRITE_8 (struct schizo_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  STX_CTRL_CE_AFAR ; 
 int STX_CTRL_CE_AFSR_ERRPNDG ; 
 int /*<<< orphan*/  STX_CTRL_UE_AFSR ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,unsigned long long,unsigned long long) ; 
 int /*<<< orphan*/  mtx_lock_spin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_unlock_spin (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
schizo_ce(void *arg)
{
	struct schizo_softc *sc = arg;
	uint64_t afar, afsr;
	int i;

	mtx_lock_spin(sc->sc_mtx);

	afar = SCHIZO_CTRL_READ_8(sc, STX_CTRL_CE_AFAR);
	for (i = 0; i < 1000; i++)
		if (((afsr = SCHIZO_CTRL_READ_8(sc, STX_CTRL_UE_AFSR)) &
		    STX_CTRL_CE_AFSR_ERRPNDG) == 0)
			break;
	sc->sc_stats_dma_ce++;
	device_printf(sc->sc_dev,
	    "correctable DMA error AFAR %#llx AFSR %#llx\n",
	    (unsigned long long)afar, (unsigned long long)afsr);

	/* Clear the error bits that we caught. */
	SCHIZO_CTRL_WRITE_8(sc, STX_CTRL_UE_AFSR, afsr);

	mtx_unlock_spin(sc->sc_mtx);

	return (FILTER_HANDLED);
}