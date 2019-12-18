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
struct ifnet {struct an_softc* if_softc; } ;
struct an_softc {int /*<<< orphan*/  mpi350; } ;

/* Variables and functions */
 int /*<<< orphan*/  AN_SW0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AN_SW1 (int /*<<< orphan*/ ) ; 
 int CSR_READ_2 (struct an_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_2 (struct an_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  FLASH_DELAY (struct an_softc*,int) ; 
 int /*<<< orphan*/  if_printf (struct ifnet*,char*) ; 

__attribute__((used)) static int
flashpchar(struct ifnet *ifp, int byte, int dwelltime)
{
	int		echo;
	int		pollbusy, waittime;
	struct an_softc	*sc = ifp->if_softc;

	byte |= 0x8000;

	if (dwelltime == 0)
		dwelltime = 200;

	waittime = dwelltime;

	/*
	 * Wait for busy bit d15 to go false indicating buffer empty
	 */
	do {
		pollbusy = CSR_READ_2(sc, AN_SW0(sc->mpi350));

		if (pollbusy & 0x8000) {
			FLASH_DELAY(sc, 50);
			waittime -= 50;
			continue;
		} else
			break;
	}
	while (waittime >= 0);

	/* timeout for busy clear wait */

	if (waittime <= 0) {
		if_printf(ifp, "flash putchar busywait timeout!\n");
		return -1;
	}
	/*
	 * Port is clear now write byte and wait for it to echo back
	 */
	do {
		CSR_WRITE_2(sc, AN_SW0(sc->mpi350), byte);
		FLASH_DELAY(sc, 50);
		dwelltime -= 50;
		echo = CSR_READ_2(sc, AN_SW1(sc->mpi350));
	} while (dwelltime >= 0 && echo != byte);


	CSR_WRITE_2(sc, AN_SW1(sc->mpi350), 0);

	return echo == byte;
}