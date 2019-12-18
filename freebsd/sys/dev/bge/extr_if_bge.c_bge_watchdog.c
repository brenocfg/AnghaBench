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
struct bge_softc {scalar_t__ bge_timer; int /*<<< orphan*/  bge_ifp; } ;
typedef  int /*<<< orphan*/  if_t ;

/* Variables and functions */
 int /*<<< orphan*/  BGE_LOCK_ASSERT (struct bge_softc*) ; 
 int BGE_RXMODE_FLOWCTL_ENABLE ; 
 int BGE_RXSTAT_RCVD_XOFF ; 
 int BGE_RXSTAT_RCVD_XON ; 
 int BGE_RXSTAT_REMOTE_XOFFED ; 
 int /*<<< orphan*/  BGE_RX_MODE ; 
 int /*<<< orphan*/  BGE_RX_STS ; 
 void* BGE_TX_TIMEOUT ; 
 int CSR_READ_4 (struct bge_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct bge_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IFCOUNTER_OERRORS ; 
 int /*<<< orphan*/  IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  bge_init_locked (struct bge_softc*) ; 
 int /*<<< orphan*/  if_inc_counter (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  if_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  if_setdrvflagbits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bge_watchdog(struct bge_softc *sc)
{
	if_t ifp;
	uint32_t status;

	BGE_LOCK_ASSERT(sc);

	if (sc->bge_timer == 0 || --sc->bge_timer)
		return;

	/* If pause frames are active then don't reset the hardware. */
	if ((CSR_READ_4(sc, BGE_RX_MODE) & BGE_RXMODE_FLOWCTL_ENABLE) != 0) {
		status = CSR_READ_4(sc, BGE_RX_STS);
		if ((status & BGE_RXSTAT_REMOTE_XOFFED) != 0) {
			/*
			 * If link partner has us in XOFF state then wait for
			 * the condition to clear.
			 */
			CSR_WRITE_4(sc, BGE_RX_STS, status);
			sc->bge_timer = BGE_TX_TIMEOUT;
			return;
		} else if ((status & BGE_RXSTAT_RCVD_XOFF) != 0 &&
		    (status & BGE_RXSTAT_RCVD_XON) != 0) {
			/*
			 * If link partner has us in XOFF state then wait for
			 * the condition to clear.
			 */
			CSR_WRITE_4(sc, BGE_RX_STS, status);
			sc->bge_timer = BGE_TX_TIMEOUT;
			return;
		}
		/*
		 * Any other condition is unexpected and the controller
		 * should be reset.
		 */
	}

	ifp = sc->bge_ifp;

	if_printf(ifp, "watchdog timeout -- resetting\n");

	if_setdrvflagbits(ifp, 0, IFF_DRV_RUNNING);
	bge_init_locked(sc);

	if_inc_counter(ifp, IFCOUNTER_OERRORS, 1);
}