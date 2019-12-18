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
struct ifnet {struct bce_softc* if_softc; } ;
struct bce_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCE_LOCK (struct bce_softc*) ; 
 int /*<<< orphan*/  BCE_UNLOCK (struct bce_softc*) ; 
 int /*<<< orphan*/  BCE_VERBOSE_SEND ; 
 int /*<<< orphan*/  DBENTER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DBEXIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bce_start_locked (struct ifnet*) ; 

__attribute__((used)) static void
bce_start(struct ifnet *ifp)
{
	struct bce_softc *sc = ifp->if_softc;

	DBENTER(BCE_VERBOSE_SEND);

	BCE_LOCK(sc);
	bce_start_locked(ifp);
	BCE_UNLOCK(sc);

	DBEXIT(BCE_VERBOSE_SEND);
}