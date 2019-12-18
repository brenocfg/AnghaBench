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
struct mpr_softc {int wait_for_port_enable; } ;

/* Variables and functions */
 int /*<<< orphan*/  mprsas_send_portenable (struct mpr_softc*) ; 

int
mprsas_startup(struct mpr_softc *sc)
{
	/*
	 * Send the port enable message and set the wait_for_port_enable flag.
	 * This flag helps to keep the simq frozen until all discovery events
	 * are processed.
	 */
	sc->wait_for_port_enable = 1;
	mprsas_send_portenable(sc);
	return (0);
}