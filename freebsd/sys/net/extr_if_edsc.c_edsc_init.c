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
struct edsc_softc {struct ifnet* sc_ifp; } ;
struct edsc_soft {struct ifnet* sc_ifp; } ;

/* Variables and functions */

__attribute__((used)) static void
edsc_init(void *dummy)
{
#if 0	/* what a hardware driver would do here... */
	struct edsc_soft	*sc = (struct edsc_softc *)dummy;
	struct ifnet		*ifp = sc->sc_ifp;

	/* blah-blah-blah */
#endif
}