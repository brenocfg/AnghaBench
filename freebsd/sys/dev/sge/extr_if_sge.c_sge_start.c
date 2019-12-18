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
struct sge_softc {int dummy; } ;
struct ifnet {struct sge_softc* if_softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  SGE_LOCK (struct sge_softc*) ; 
 int /*<<< orphan*/  SGE_UNLOCK (struct sge_softc*) ; 
 int /*<<< orphan*/  sge_start_locked (struct ifnet*) ; 

__attribute__((used)) static void
sge_start(struct ifnet *ifp)
{
	struct sge_softc *sc;

	sc = ifp->if_softc;
	SGE_LOCK(sc);
	sge_start_locked(ifp);
	SGE_UNLOCK(sc);
}