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
struct rt_softc {struct ifnet* ifp; } ;
struct ifnet {int if_flags; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int IFF_UP ; 
 int /*<<< orphan*/  RT_DEBUG_ANY ; 
 int /*<<< orphan*/  RT_DPRINTF (struct rt_softc*,int /*<<< orphan*/ ,char*) ; 
 struct rt_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt_init (struct rt_softc*) ; 

__attribute__((used)) static int
rt_resume(device_t dev)
{
	struct rt_softc *sc;
	struct ifnet *ifp;

	sc = device_get_softc(dev);
	ifp = sc->ifp;

	RT_DPRINTF(sc, RT_DEBUG_ANY, "resuming\n");

	if (ifp->if_flags & IFF_UP)
		rt_init(sc);

	return (0);
}