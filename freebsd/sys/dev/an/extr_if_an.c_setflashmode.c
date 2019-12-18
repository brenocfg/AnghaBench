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
 int /*<<< orphan*/  AN_COMMAND (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AN_SW0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AN_SW1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AN_TIMEOUT ; 
 int /*<<< orphan*/  CSR_WRITE_2 (struct an_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EIO ; 
 int /*<<< orphan*/  FLASH_COMMAND ; 
 int /*<<< orphan*/  FLASH_DELAY (struct an_softc*,int) ; 
 int WaitBusy (struct ifnet*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static int
setflashmode(struct ifnet *ifp)
{
	int		status;
	struct an_softc	*sc = ifp->if_softc;

	CSR_WRITE_2(sc, AN_SW0(sc->mpi350), FLASH_COMMAND);
	CSR_WRITE_2(sc, AN_SW1(sc->mpi350), FLASH_COMMAND);
	CSR_WRITE_2(sc, AN_SW0(sc->mpi350), FLASH_COMMAND);
	CSR_WRITE_2(sc, AN_COMMAND(sc->mpi350), FLASH_COMMAND);

	/*
	 * mdelay(500); // 500ms delay
	 */

	FLASH_DELAY(sc, 500);

	if (!(status = WaitBusy(ifp, AN_TIMEOUT))) {
		printf("Waitbusy hang after setflash mode\n");
		return -EIO;
	}
	return 0;
}