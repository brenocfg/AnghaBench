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
struct ipw_softc {int /*<<< orphan*/  flags; int /*<<< orphan*/  sc_dev; } ;

/* Variables and functions */
 int CSR_READ_4 (struct ipw_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct ipw_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  IPW_CSR_INTR_MASK ; 
 int /*<<< orphan*/  IPW_CSR_RST ; 
 int /*<<< orphan*/  IPW_FLAG_HAS_RADIO_SWITCH ; 
 int IPW_RST_MASTER_DISABLED ; 
 int IPW_RST_PRINCETON_RESET ; 
 int IPW_RST_STOP_MASTER ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
ipw_stop_master(struct ipw_softc *sc)
{
	uint32_t tmp;
	int ntries;

	/* disable interrupts */
	CSR_WRITE_4(sc, IPW_CSR_INTR_MASK, 0);

	CSR_WRITE_4(sc, IPW_CSR_RST, IPW_RST_STOP_MASTER);
	for (ntries = 0; ntries < 50; ntries++) {
		if (CSR_READ_4(sc, IPW_CSR_RST) & IPW_RST_MASTER_DISABLED)
			break;
		DELAY(10);
	}
	if (ntries == 50)
		device_printf(sc->sc_dev, "timeout waiting for master\n");

	tmp = CSR_READ_4(sc, IPW_CSR_RST);
	CSR_WRITE_4(sc, IPW_CSR_RST, tmp | IPW_RST_PRINCETON_RESET);

	/* Clear all flags except the following */
	sc->flags &= IPW_FLAG_HAS_RADIO_SWITCH;
}