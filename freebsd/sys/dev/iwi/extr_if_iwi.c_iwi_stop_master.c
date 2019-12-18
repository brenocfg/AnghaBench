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
struct iwi_softc {int /*<<< orphan*/  flags; int /*<<< orphan*/  sc_dev; } ;

/* Variables and functions */
 int CSR_READ_4 (struct iwi_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct iwi_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  IWI_CSR_INTR_MASK ; 
 int /*<<< orphan*/  IWI_CSR_RST ; 
 int /*<<< orphan*/  IWI_FLAG_FW_INITED ; 
 int IWI_RST_MASTER_DISABLED ; 
 int IWI_RST_PRINCETON_RESET ; 
 int IWI_RST_STOP_MASTER ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
iwi_stop_master(struct iwi_softc *sc)
{
	uint32_t tmp;
	int ntries;

	/* disable interrupts */
	CSR_WRITE_4(sc, IWI_CSR_INTR_MASK, 0);

	CSR_WRITE_4(sc, IWI_CSR_RST, IWI_RST_STOP_MASTER);
	for (ntries = 0; ntries < 5; ntries++) {
		if (CSR_READ_4(sc, IWI_CSR_RST) & IWI_RST_MASTER_DISABLED)
			break;
		DELAY(10);
	}
	if (ntries == 5)
		device_printf(sc->sc_dev, "timeout waiting for master\n");

	tmp = CSR_READ_4(sc, IWI_CSR_RST);
	CSR_WRITE_4(sc, IWI_CSR_RST, tmp | IWI_RST_PRINCETON_RESET);

	sc->flags &= ~IWI_FLAG_FW_INITED;
}