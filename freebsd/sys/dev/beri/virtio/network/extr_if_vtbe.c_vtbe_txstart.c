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
struct vtbe_softc {int dummy; } ;
struct ifnet {struct vtbe_softc* if_softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  VTBE_LOCK (struct vtbe_softc*) ; 
 int /*<<< orphan*/  VTBE_UNLOCK (struct vtbe_softc*) ; 
 int /*<<< orphan*/  vtbe_txstart_locked (struct vtbe_softc*) ; 

__attribute__((used)) static void
vtbe_txstart(struct ifnet *ifp)
{
	struct vtbe_softc *sc = ifp->if_softc;

	VTBE_LOCK(sc);
	vtbe_txstart_locked(sc);
	VTBE_UNLOCK(sc);
}