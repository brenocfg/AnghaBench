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
struct ifnet {struct ffec_softc* if_softc; } ;
struct ffec_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FFEC_LOCK (struct ffec_softc*) ; 
 int /*<<< orphan*/  FFEC_UNLOCK (struct ffec_softc*) ; 
 int /*<<< orphan*/  ffec_txstart_locked (struct ffec_softc*) ; 

__attribute__((used)) static void
ffec_txstart(struct ifnet *ifp)
{
	struct ffec_softc *sc = ifp->if_softc;

	FFEC_LOCK(sc);
	ffec_txstart_locked(sc);
	FFEC_UNLOCK(sc);
}