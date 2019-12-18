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
struct sfxge_port {scalar_t__ init_state; } ;
struct sfxge_softc {struct sfxge_port port; int /*<<< orphan*/ * enp; } ;
typedef  int /*<<< orphan*/  efx_nic_t ;
typedef  int /*<<< orphan*/  efx_link_mode_t ;

/* Variables and functions */
 int /*<<< orphan*/  SFXGE_PORT_LOCK (struct sfxge_port*) ; 
 scalar_t__ SFXGE_PORT_STARTED ; 
 int /*<<< orphan*/  SFXGE_PORT_UNLOCK (struct sfxge_port*) ; 
 scalar_t__ __predict_false (int) ; 
 int /*<<< orphan*/  efx_port_poll (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sfxge_mac_link_update (struct sfxge_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
sfxge_mac_poll_work(void *arg, int npending)
{
	struct sfxge_softc *sc;
	efx_nic_t *enp;
	struct sfxge_port *port;
	efx_link_mode_t mode;

	sc = (struct sfxge_softc *)arg;
	enp = sc->enp;
	port = &sc->port;

	SFXGE_PORT_LOCK(port);

	if (__predict_false(port->init_state != SFXGE_PORT_STARTED))
		goto done;

	/* This may sleep waiting for MCDI completion */
	(void)efx_port_poll(enp, &mode);
	sfxge_mac_link_update(sc, mode);

done:
	SFXGE_PORT_UNLOCK(port);
}