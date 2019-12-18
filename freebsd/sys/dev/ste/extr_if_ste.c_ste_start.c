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
struct ste_softc {int dummy; } ;
struct ifnet {struct ste_softc* if_softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  STE_LOCK (struct ste_softc*) ; 
 int /*<<< orphan*/  STE_UNLOCK (struct ste_softc*) ; 
 int /*<<< orphan*/  ste_start_locked (struct ifnet*) ; 

__attribute__((used)) static void
ste_start(struct ifnet *ifp)
{
	struct ste_softc *sc;

	sc = ifp->if_softc;
	STE_LOCK(sc);
	ste_start_locked(ifp);
	STE_UNLOCK(sc);
}