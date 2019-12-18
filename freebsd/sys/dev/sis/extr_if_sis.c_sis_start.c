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
struct sis_softc {int dummy; } ;
struct ifnet {struct sis_softc* if_softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIS_LOCK (struct sis_softc*) ; 
 int /*<<< orphan*/  SIS_UNLOCK (struct sis_softc*) ; 
 int /*<<< orphan*/  sis_startl (struct ifnet*) ; 

__attribute__((used)) static void
sis_start(struct ifnet *ifp)
{
	struct sis_softc	*sc;

	sc = ifp->if_softc;
	SIS_LOCK(sc);
	sis_startl(ifp);
	SIS_UNLOCK(sc);
}