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
struct hifn_softc {scalar_t__ sc_suspended; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int if_flags; } ;

/* Variables and functions */
 int IFF_UP ; 
 struct hifn_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 TYPE_1__* ifp ; 
 int /*<<< orphan*/  rl_init (struct hifn_softc*) ; 

__attribute__((used)) static int
hifn_resume(device_t dev)
{
	struct hifn_softc *sc = device_get_softc(dev);
#ifdef notyet
        /* reinitialize interface if necessary */
        if (ifp->if_flags & IFF_UP)
                rl_init(sc);
#endif
	sc->sc_suspended = 0;

	return (0);
}