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
 int AN_CMD_BUSY ; 
 int /*<<< orphan*/  AN_COMMAND (int /*<<< orphan*/ ) ; 
 int CSR_READ_2 (struct an_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FLASH_DELAY (struct an_softc*,int) ; 
 int /*<<< orphan*/  unstickbusy (struct ifnet*) ; 

__attribute__((used)) static int
WaitBusy(struct ifnet *ifp, int uSec)
{
	int		statword = 0xffff;
	int		delay = 0;
	struct an_softc	*sc = ifp->if_softc;

	while ((statword & AN_CMD_BUSY) && delay <= (1000 * 100)) {
		FLASH_DELAY(sc, 10);
		delay += 10;
		statword = CSR_READ_2(sc, AN_COMMAND(sc->mpi350));

		if ((AN_CMD_BUSY & statword) && (delay % 200)) {
			unstickbusy(ifp);
		}
	}

	return 0 == (AN_CMD_BUSY & statword);
}