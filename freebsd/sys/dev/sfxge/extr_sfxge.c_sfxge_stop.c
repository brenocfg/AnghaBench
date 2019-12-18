#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sfxge_softc {scalar_t__ init_state; TYPE_1__* ifnet; int /*<<< orphan*/  enp; } ;
struct TYPE_2__ {int /*<<< orphan*/  if_drv_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  SFXGE_ADAPTER_LOCK_ASSERT_OWNED (struct sfxge_softc*) ; 
 scalar_t__ SFXGE_REGISTERED ; 
 scalar_t__ SFXGE_STARTED ; 
 int /*<<< orphan*/  efx_nic_fini (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sfxge_ev_stop (struct sfxge_softc*) ; 
 int /*<<< orphan*/  sfxge_intr_stop (struct sfxge_softc*) ; 
 int /*<<< orphan*/  sfxge_port_stop (struct sfxge_softc*) ; 
 int /*<<< orphan*/  sfxge_rx_stop (struct sfxge_softc*) ; 
 int /*<<< orphan*/  sfxge_tx_stop (struct sfxge_softc*) ; 

__attribute__((used)) static void
sfxge_stop(struct sfxge_softc *sc)
{
	SFXGE_ADAPTER_LOCK_ASSERT_OWNED(sc);

	if (sc->init_state != SFXGE_STARTED)
		return;

	sc->init_state = SFXGE_REGISTERED;

	/* Stop the transmitter. */
	sfxge_tx_stop(sc);

	/* Stop the receiver. */
	sfxge_rx_stop(sc);

	/* Stop the port. */
	sfxge_port_stop(sc);

	/* Stop processing events. */
	sfxge_ev_stop(sc);

	/* Stop processing interrupts. */
	sfxge_intr_stop(sc);

	efx_nic_fini(sc->enp);

	sc->ifnet->if_drv_flags &= ~IFF_DRV_RUNNING;
}