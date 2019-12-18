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
struct iwi_softc {int /*<<< orphan*/  sc_dev; } ;

/* Variables and functions */
 int CSR_READ_4 (struct iwi_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct iwi_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int EIO ; 
 int /*<<< orphan*/  IWI_CSR_AUTOINC_ADDR ; 
 int /*<<< orphan*/  IWI_CSR_AUTOINC_DATA ; 
 int /*<<< orphan*/  IWI_CSR_CTL ; 
 int /*<<< orphan*/  IWI_CSR_READ_INT ; 
 int /*<<< orphan*/  IWI_CSR_RST ; 
 int IWI_CTL_CLOCK_READY ; 
 int IWI_CTL_INIT ; 
 int IWI_READ_INT_INIT_HOST ; 
 int IWI_RST_SOFT_RESET ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  iwi_stop_master (struct iwi_softc*) ; 

__attribute__((used)) static int
iwi_reset(struct iwi_softc *sc)
{
	uint32_t tmp;
	int i, ntries;

	iwi_stop_master(sc);

	tmp = CSR_READ_4(sc, IWI_CSR_CTL);
	CSR_WRITE_4(sc, IWI_CSR_CTL, tmp | IWI_CTL_INIT);

	CSR_WRITE_4(sc, IWI_CSR_READ_INT, IWI_READ_INT_INIT_HOST);

	/* wait for clock stabilization */
	for (ntries = 0; ntries < 1000; ntries++) {
		if (CSR_READ_4(sc, IWI_CSR_CTL) & IWI_CTL_CLOCK_READY)
			break;
		DELAY(200);
	}
	if (ntries == 1000) {
		device_printf(sc->sc_dev,
		    "timeout waiting for clock stabilization\n");
		return EIO;
	}

	tmp = CSR_READ_4(sc, IWI_CSR_RST);
	CSR_WRITE_4(sc, IWI_CSR_RST, tmp | IWI_RST_SOFT_RESET);

	DELAY(10);

	tmp = CSR_READ_4(sc, IWI_CSR_CTL);
	CSR_WRITE_4(sc, IWI_CSR_CTL, tmp | IWI_CTL_INIT);

	/* clear NIC memory */
	CSR_WRITE_4(sc, IWI_CSR_AUTOINC_ADDR, 0);
	for (i = 0; i < 0xc000; i++)
		CSR_WRITE_4(sc, IWI_CSR_AUTOINC_DATA, 0);

	return 0;
}