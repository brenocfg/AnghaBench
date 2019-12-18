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
 int /*<<< orphan*/  BCE_VERBOSE ; 
 int /*<<< orphan*/  DBENTER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DBEXIT (int /*<<< orphan*/ ) ; 
 int bce_ifmedia_upd_locked (struct ifnet*) ; 

__attribute__((used)) static int
bce_ifmedia_upd(struct ifnet *ifp)
{
	struct bce_softc *sc = ifp->if_softc;
	int error;

	DBENTER(BCE_VERBOSE);

	BCE_LOCK(sc);
	error = bce_ifmedia_upd_locked(ifp);
	BCE_UNLOCK(sc);

	DBEXIT(BCE_VERBOSE);
	return (error);
}