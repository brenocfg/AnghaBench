#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ ic_nrunning; } ;
struct rt2860_softc {TYPE_1__ sc_ic; } ;

/* Variables and functions */
 int /*<<< orphan*/  rt2860_init (struct rt2860_softc*) ; 

void
rt2860_resume(void *xsc)
{
	struct rt2860_softc *sc = xsc;

	if (sc->sc_ic.ic_nrunning > 0)
		rt2860_init(sc);
}