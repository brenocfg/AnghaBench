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
struct rl_softc {TYPE_1__* rl_ifp; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int /*<<< orphan*/  if_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFF_UP ; 
 int /*<<< orphan*/  RL_LOCK (struct rl_softc*) ; 
 int /*<<< orphan*/  RL_UNLOCK (struct rl_softc*) ; 
 struct rl_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rl_setwol (struct rl_softc*) ; 
 int /*<<< orphan*/  rl_stop (struct rl_softc*) ; 

__attribute__((used)) static int
rl_shutdown(device_t dev)
{
	struct rl_softc		*sc;

	sc = device_get_softc(dev);

	RL_LOCK(sc);
	rl_stop(sc);
	/*
	 * Mark interface as down since otherwise we will panic if
	 * interrupt comes in later on, which can happen in some
	 * cases.
	 */
	sc->rl_ifp->if_flags &= ~IFF_UP;
	rl_setwol(sc);
	RL_UNLOCK(sc);

	return (0);
}