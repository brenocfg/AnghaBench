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
struct rl_softc {int rl_flags; scalar_t__ suspended; struct ifnet* rl_ifp; } ;
struct ifnet {int if_flags; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int CSR_READ_1 (struct rl_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_1 (struct rl_softc*,int /*<<< orphan*/ ,int) ; 
 int IFF_UP ; 
 int RL_FLAG_MACSLEEP ; 
 int /*<<< orphan*/  RL_GPIO ; 
 int /*<<< orphan*/  RL_LOCK (struct rl_softc*) ; 
 int /*<<< orphan*/  RL_MACDBG ; 
 int /*<<< orphan*/  RL_UNLOCK (struct rl_softc*) ; 
 struct rl_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  re_clrwol (struct rl_softc*) ; 
 int /*<<< orphan*/  re_init_locked (struct rl_softc*) ; 

__attribute__((used)) static int
re_resume(device_t dev)
{
	struct rl_softc		*sc;
	struct ifnet		*ifp;

	sc = device_get_softc(dev);

	RL_LOCK(sc);

	ifp = sc->rl_ifp;
	/* Take controller out of sleep mode. */
	if ((sc->rl_flags & RL_FLAG_MACSLEEP) != 0) {
		if ((CSR_READ_1(sc, RL_MACDBG) & 0x80) == 0x80)
			CSR_WRITE_1(sc, RL_GPIO,
			    CSR_READ_1(sc, RL_GPIO) | 0x01);
	}

	/*
	 * Clear WOL matching such that normal Rx filtering
	 * wouldn't interfere with WOL patterns.
	 */
	re_clrwol(sc);

	/* reinitialize interface if necessary */
	if (ifp->if_flags & IFF_UP)
		re_init_locked(sc);

	sc->suspended = 0;
	RL_UNLOCK(sc);

	return (0);
}