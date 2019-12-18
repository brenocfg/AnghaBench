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
struct sfxge_softc {scalar_t__ init_state; int /*<<< orphan*/  dev; int /*<<< orphan*/  enp; TYPE_1__* ifnet; } ;
struct TYPE_2__ {int /*<<< orphan*/  if_drv_flags; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IFF_DRV_OACTIVE ; 
 int /*<<< orphan*/  IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  SFXGE_ADAPTER_LOCK_ASSERT_OWNED (struct sfxge_softc*) ; 
 scalar_t__ SFXGE_REGISTERED ; 
 scalar_t__ SFXGE_STARTED ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  efx_nic_fini (int /*<<< orphan*/ ) ; 
 int efx_nic_init (int /*<<< orphan*/ ) ; 
 int sfxge_ev_start (struct sfxge_softc*) ; 
 int /*<<< orphan*/  sfxge_ev_stop (struct sfxge_softc*) ; 
 int sfxge_intr_start (struct sfxge_softc*) ; 
 int /*<<< orphan*/  sfxge_intr_stop (struct sfxge_softc*) ; 
 int sfxge_port_start (struct sfxge_softc*) ; 
 int /*<<< orphan*/  sfxge_port_stop (struct sfxge_softc*) ; 
 int sfxge_rx_start (struct sfxge_softc*) ; 
 int /*<<< orphan*/  sfxge_rx_stop (struct sfxge_softc*) ; 
 int sfxge_set_drv_limits (struct sfxge_softc*) ; 
 int sfxge_tx_start (struct sfxge_softc*) ; 

__attribute__((used)) static int
sfxge_start(struct sfxge_softc *sc)
{
	int rc;

	SFXGE_ADAPTER_LOCK_ASSERT_OWNED(sc);

	if (sc->init_state == SFXGE_STARTED)
		return (0);

	if (sc->init_state != SFXGE_REGISTERED) {
		rc = EINVAL;
		goto fail;
	}

	/* Set required resource limits */
	if ((rc = sfxge_set_drv_limits(sc)) != 0)
		goto fail;

	if ((rc = efx_nic_init(sc->enp)) != 0)
		goto fail;

	/* Start processing interrupts. */
	if ((rc = sfxge_intr_start(sc)) != 0)
		goto fail2;

	/* Start processing events. */
	if ((rc = sfxge_ev_start(sc)) != 0)
		goto fail3;

	/* Fire up the port. */
	if ((rc = sfxge_port_start(sc)) != 0)
		goto fail4;

	/* Start the receiver side. */
	if ((rc = sfxge_rx_start(sc)) != 0)
		goto fail5;

	/* Start the transmitter side. */
	if ((rc = sfxge_tx_start(sc)) != 0)
		goto fail6;

	sc->init_state = SFXGE_STARTED;

	/* Tell the stack we're running. */
	sc->ifnet->if_drv_flags |= IFF_DRV_RUNNING;
	sc->ifnet->if_drv_flags &= ~IFF_DRV_OACTIVE;

	return (0);

fail6:
	sfxge_rx_stop(sc);

fail5:
	sfxge_port_stop(sc);

fail4:
	sfxge_ev_stop(sc);

fail3:
	sfxge_intr_stop(sc);

fail2:
	efx_nic_fini(sc->enp);

fail:
	device_printf(sc->dev, "sfxge_start: %d\n", rc);

	return (rc);
}