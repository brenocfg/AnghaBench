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
 int /*<<< orphan*/  AN_CMD_DISABLE ; 
 int /*<<< orphan*/  AN_CMD_FW_RESTART ; 
 int /*<<< orphan*/  AN_COMMAND (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AN_LOCK (struct an_softc*) ; 
 int AN_TIMEOUT ; 
 int /*<<< orphan*/  AN_UNLOCK (struct an_softc*) ; 
 int /*<<< orphan*/  CSR_WRITE_2 (struct an_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EBUSY ; 
 int /*<<< orphan*/  FLASH_DELAY (struct an_softc*,int) ; 
 int WaitBusy (struct ifnet*,int) ; 
 int /*<<< orphan*/  an_cmd (struct an_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  an_stop (struct an_softc*) ; 
 int /*<<< orphan*/  if_printf (struct ifnet*,char*,int) ; 

__attribute__((used)) static int
cmdreset(struct ifnet *ifp)
{
	int		status;
	struct an_softc	*sc = ifp->if_softc;

	AN_LOCK(sc);
	an_stop(sc);

	an_cmd(sc, AN_CMD_DISABLE, 0);

	if (!(status = WaitBusy(ifp, AN_TIMEOUT))) {
		if_printf(ifp, "Waitbusy hang b4 RESET =%d\n", status);
		AN_UNLOCK(sc);
		return -EBUSY;
	}
	CSR_WRITE_2(sc, AN_COMMAND(sc->mpi350), AN_CMD_FW_RESTART);

	FLASH_DELAY(sc, 1000);	/* WAS 600 12/7/00 */


	if (!(status = WaitBusy(ifp, 100))) {
		if_printf(ifp, "Waitbusy hang AFTER RESET =%d\n", status);
		AN_UNLOCK(sc);
		return -EBUSY;
	}
	AN_UNLOCK(sc);
	return 0;
}