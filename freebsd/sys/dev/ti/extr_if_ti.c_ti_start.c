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
struct ti_softc {int dummy; } ;
struct ifnet {struct ti_softc* if_softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  TI_LOCK (struct ti_softc*) ; 
 int /*<<< orphan*/  TI_UNLOCK (struct ti_softc*) ; 
 int /*<<< orphan*/  ti_start_locked (struct ifnet*) ; 

__attribute__((used)) static void
ti_start(struct ifnet *ifp)
{
	struct ti_softc *sc;

	sc = ifp->if_softc;
	TI_LOCK(sc);
	ti_start_locked(ifp);
	TI_UNLOCK(sc);
}