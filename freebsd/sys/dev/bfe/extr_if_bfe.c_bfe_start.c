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
struct ifnet {scalar_t__ if_softc; } ;
struct bfe_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFE_LOCK (struct bfe_softc*) ; 
 int /*<<< orphan*/  BFE_UNLOCK (struct bfe_softc*) ; 
 int /*<<< orphan*/  bfe_start_locked (struct ifnet*) ; 

__attribute__((used)) static void
bfe_start(struct ifnet *ifp)
{
	BFE_LOCK((struct bfe_softc *)ifp->if_softc);
	bfe_start_locked(ifp);
	BFE_UNLOCK((struct bfe_softc *)ifp->if_softc);
}