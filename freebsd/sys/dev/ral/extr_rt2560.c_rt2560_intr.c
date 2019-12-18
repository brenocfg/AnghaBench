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
struct rt2560_softc {int sc_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  RAL_LOCK (struct rt2560_softc*) ; 
 int RAL_READ (struct rt2560_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RAL_UNLOCK (struct rt2560_softc*) ; 
 int /*<<< orphan*/  RAL_WRITE (struct rt2560_softc*,int /*<<< orphan*/ ,int) ; 
 int RT2560_BEACON_EXPIRE ; 
 int /*<<< orphan*/  RT2560_CSR7 ; 
 int /*<<< orphan*/  RT2560_CSR8 ; 
 int RT2560_DECRYPTION_DONE ; 
 int RT2560_ENCRYPTION_DONE ; 
 int RT2560_F_RUNNING ; 
 int RT2560_INTR_MASK ; 
 int RT2560_PRIO_DONE ; 
 int RT2560_RX_DONE ; 
 int RT2560_TX_DONE ; 
 int RT2560_WAKEUP_EXPIRE ; 
 int /*<<< orphan*/  rt2560_beacon_expire (struct rt2560_softc*) ; 
 int /*<<< orphan*/  rt2560_decryption_intr (struct rt2560_softc*) ; 
 int /*<<< orphan*/  rt2560_encryption_intr (struct rt2560_softc*) ; 
 int /*<<< orphan*/  rt2560_prio_intr (struct rt2560_softc*) ; 
 int /*<<< orphan*/  rt2560_rx_intr (struct rt2560_softc*) ; 
 int /*<<< orphan*/  rt2560_tx_intr (struct rt2560_softc*) ; 
 int /*<<< orphan*/  rt2560_wakeup_expire (struct rt2560_softc*) ; 

void
rt2560_intr(void *arg)
{
	struct rt2560_softc *sc = arg;
	uint32_t r;

	RAL_LOCK(sc);

	/* disable interrupts */
	RAL_WRITE(sc, RT2560_CSR8, 0xffffffff);

	/* don't re-enable interrupts if we're shutting down */
	if (!(sc->sc_flags & RT2560_F_RUNNING)) {
		RAL_UNLOCK(sc);
		return;
	}

	r = RAL_READ(sc, RT2560_CSR7);
	RAL_WRITE(sc, RT2560_CSR7, r);

	if (r & RT2560_BEACON_EXPIRE)
		rt2560_beacon_expire(sc);

	if (r & RT2560_WAKEUP_EXPIRE)
		rt2560_wakeup_expire(sc);

	if (r & RT2560_ENCRYPTION_DONE)
		rt2560_encryption_intr(sc);

	if (r & RT2560_TX_DONE)
		rt2560_tx_intr(sc);

	if (r & RT2560_PRIO_DONE)
		rt2560_prio_intr(sc);

	if (r & RT2560_DECRYPTION_DONE)
		rt2560_decryption_intr(sc);

	if (r & RT2560_RX_DONE) {
		rt2560_rx_intr(sc);
		rt2560_encryption_intr(sc);
	}

	/* re-enable interrupts */
	RAL_WRITE(sc, RT2560_CSR8, RT2560_INTR_MASK);

	RAL_UNLOCK(sc);
}