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
struct ipw_softc {int dummy; } ;

/* Variables and functions */
 int CSR_READ_4 (struct ipw_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct ipw_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int EIO ; 
 int /*<<< orphan*/  IPW_CSR_CTL ; 
 int /*<<< orphan*/  IPW_CSR_RST ; 
 int IPW_CTL_CLOCK_READY ; 
 int IPW_CTL_INIT ; 
 int IPW_RST_SW_RESET ; 
 int /*<<< orphan*/  ipw_stop_master (struct ipw_softc*) ; 

__attribute__((used)) static int
ipw_reset(struct ipw_softc *sc)
{
	uint32_t tmp;
	int ntries;

	ipw_stop_master(sc);

	/* move adapter to D0 state */
	tmp = CSR_READ_4(sc, IPW_CSR_CTL);
	CSR_WRITE_4(sc, IPW_CSR_CTL, tmp | IPW_CTL_INIT);

	/* wait for clock stabilization */
	for (ntries = 0; ntries < 1000; ntries++) {
		if (CSR_READ_4(sc, IPW_CSR_CTL) & IPW_CTL_CLOCK_READY)
			break;
		DELAY(200);
	}
	if (ntries == 1000)
		return EIO;

	tmp =  CSR_READ_4(sc, IPW_CSR_RST);
	CSR_WRITE_4(sc, IPW_CSR_RST, tmp | IPW_RST_SW_RESET);

	DELAY(10);

	tmp = CSR_READ_4(sc, IPW_CSR_CTL);
	CSR_WRITE_4(sc, IPW_CSR_CTL, tmp | IPW_CTL_INIT);

	return 0;
}