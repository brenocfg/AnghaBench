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
struct ifaddr {struct carp_softc* ifa_carp; } ;
struct carp_softc {scalar_t__ sc_state; } ;

/* Variables and functions */
 scalar_t__ MASTER ; 

int
carp_master(struct ifaddr *ifa)
{
	struct carp_softc *sc = ifa->ifa_carp;

	return (sc->sc_state == MASTER);
}