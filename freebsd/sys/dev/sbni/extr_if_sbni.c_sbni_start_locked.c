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
struct sbni_softc {scalar_t__ tx_frameno; } ;
struct ifnet {struct sbni_softc* if_softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  prepare_to_send (struct sbni_softc*) ; 

__attribute__((used)) static void
sbni_start_locked(struct ifnet *ifp)
{
	struct sbni_softc *sc = ifp->if_softc;

	if (sc->tx_frameno == 0)
		prepare_to_send(sc);
}