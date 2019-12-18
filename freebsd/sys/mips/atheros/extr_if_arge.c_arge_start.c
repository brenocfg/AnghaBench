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
struct ifnet {struct arge_softc* if_softc; } ;
struct arge_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARGE_LOCK (struct arge_softc*) ; 
 int /*<<< orphan*/  ARGE_UNLOCK (struct arge_softc*) ; 
 int /*<<< orphan*/  arge_start_locked (struct ifnet*) ; 

__attribute__((used)) static void
arge_start(struct ifnet *ifp)
{
	struct arge_softc	 *sc;

	sc = ifp->if_softc;

	ARGE_LOCK(sc);
	arge_start_locked(ifp);
	ARGE_UNLOCK(sc);
}