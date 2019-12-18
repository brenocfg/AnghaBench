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
struct tsec_softc {int dummy; } ;
struct ifnet {struct tsec_softc* if_softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  TSEC_TRANSMIT_LOCK (struct tsec_softc*) ; 
 int /*<<< orphan*/  TSEC_TRANSMIT_UNLOCK (struct tsec_softc*) ; 
 int /*<<< orphan*/  tsec_start_locked (struct ifnet*) ; 

__attribute__((used)) static void
tsec_start(struct ifnet *ifp)
{
	struct tsec_softc *sc = ifp->if_softc;

	TSEC_TRANSMIT_LOCK(sc);
	tsec_start_locked(ifp);
	TSEC_TRANSMIT_UNLOCK(sc);
}