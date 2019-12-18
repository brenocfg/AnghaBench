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
typedef  int /*<<< orphan*/  u_int ;
struct ifnet {struct epair_softc* if_softc; } ;
struct epair_softc {int /*<<< orphan*/  cpuid; } ;

/* Variables and functions */

__attribute__((used)) static u_int
cpuid_from_ifp(struct ifnet *ifp)
{
	struct epair_softc *sc;

	if (ifp == NULL)
		return (0);
	sc = ifp->if_softc;

	return (sc->cpuid);
}