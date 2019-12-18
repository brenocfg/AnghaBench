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
struct ifnet {struct fv_softc* if_softc; } ;
struct fv_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FV_LOCK (struct fv_softc*) ; 
 int /*<<< orphan*/  FV_UNLOCK (struct fv_softc*) ; 
 int /*<<< orphan*/  fv_start_locked (struct ifnet*) ; 

__attribute__((used)) static void
fv_start(struct ifnet *ifp)
{
	struct fv_softc	 *sc;

	sc = ifp->if_softc;

	FV_LOCK(sc);
	fv_start_locked(ifp);
	FV_UNLOCK(sc);
}