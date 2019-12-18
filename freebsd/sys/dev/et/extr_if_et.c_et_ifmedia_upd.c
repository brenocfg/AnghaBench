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
struct ifnet {struct et_softc* if_softc; } ;
struct et_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ET_LOCK (struct et_softc*) ; 
 int /*<<< orphan*/  ET_UNLOCK (struct et_softc*) ; 
 int et_ifmedia_upd_locked (struct ifnet*) ; 

__attribute__((used)) static int
et_ifmedia_upd(struct ifnet *ifp)
{
	struct et_softc *sc;
	int res;

	sc = ifp->if_softc;
	ET_LOCK(sc);
	res = et_ifmedia_upd_locked(ifp);
	ET_UNLOCK(sc);

	return (res);
}