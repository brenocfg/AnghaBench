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
struct ifnet {struct dwc_softc* if_softc; } ;
struct dwc_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DWC_LOCK (struct dwc_softc*) ; 
 int /*<<< orphan*/  DWC_UNLOCK (struct dwc_softc*) ; 
 int /*<<< orphan*/  dwc_txstart_locked (struct dwc_softc*) ; 

__attribute__((used)) static void
dwc_txstart(struct ifnet *ifp)
{
	struct dwc_softc *sc = ifp->if_softc;

	DWC_LOCK(sc);
	dwc_txstart_locked(sc);
	DWC_UNLOCK(sc);
}