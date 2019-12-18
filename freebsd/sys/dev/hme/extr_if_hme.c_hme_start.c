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
struct ifnet {struct hme_softc* if_softc; } ;
struct hme_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HME_LOCK (struct hme_softc*) ; 
 int /*<<< orphan*/  HME_UNLOCK (struct hme_softc*) ; 
 int /*<<< orphan*/  hme_start_locked (struct ifnet*) ; 

__attribute__((used)) static void
hme_start(struct ifnet *ifp)
{
	struct hme_softc *sc = ifp->if_softc;

	HME_LOCK(sc);
	hme_start_locked(ifp);
	HME_UNLOCK(sc);
}