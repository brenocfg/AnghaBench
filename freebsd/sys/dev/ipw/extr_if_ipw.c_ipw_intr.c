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
 int /*<<< orphan*/  IPW_CSR_INTR ; 
 int /*<<< orphan*/  IPW_CSR_INTR_MASK ; 
 int IPW_INTR_FATAL_ERROR ; 
 int IPW_INTR_FW_INIT_DONE ; 
 int IPW_INTR_MASK ; 
 int IPW_INTR_PARITY_ERROR ; 
 int IPW_INTR_RX_TRANSFER ; 
 int IPW_INTR_TX_TRANSFER ; 
 int /*<<< orphan*/  IPW_LOCK (struct ipw_softc*) ; 
 int /*<<< orphan*/  IPW_UNLOCK (struct ipw_softc*) ; 
 int /*<<< orphan*/  ipw_fatal_error_intr (struct ipw_softc*) ; 
 int /*<<< orphan*/  ipw_rx_intr (struct ipw_softc*) ; 
 int /*<<< orphan*/  ipw_tx_intr (struct ipw_softc*) ; 
 int /*<<< orphan*/  wakeup (struct ipw_softc*) ; 

__attribute__((used)) static void
ipw_intr(void *arg)
{
	struct ipw_softc *sc = arg;
	uint32_t r;

	IPW_LOCK(sc);

	r = CSR_READ_4(sc, IPW_CSR_INTR);
	if (r == 0 || r == 0xffffffff)
		goto done;

	/* disable interrupts */
	CSR_WRITE_4(sc, IPW_CSR_INTR_MASK, 0);

	/* acknowledge all interrupts */
	CSR_WRITE_4(sc, IPW_CSR_INTR, r);

	if (r & (IPW_INTR_FATAL_ERROR | IPW_INTR_PARITY_ERROR)) {
		ipw_fatal_error_intr(sc);
		goto done;
	}

	if (r & IPW_INTR_FW_INIT_DONE)
		wakeup(sc);

	if (r & IPW_INTR_RX_TRANSFER)
		ipw_rx_intr(sc);

	if (r & IPW_INTR_TX_TRANSFER)
		ipw_tx_intr(sc);

	/* re-enable interrupts */
	CSR_WRITE_4(sc, IPW_CSR_INTR_MASK, IPW_INTR_MASK);
done:
	IPW_UNLOCK(sc);
}