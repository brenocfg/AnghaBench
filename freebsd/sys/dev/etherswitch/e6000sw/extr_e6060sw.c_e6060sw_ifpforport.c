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
struct ifnet {int dummy; } ;
struct e6060sw_softc {int numports; struct ifnet** ifp; } ;

/* Variables and functions */

__attribute__((used)) static inline struct ifnet *
e6060sw_ifpforport(struct e6060sw_softc *sc, int port)
{

	if (port < 0 || port > sc->numports)
		return (NULL);
	return (sc->ifp[port]);
}