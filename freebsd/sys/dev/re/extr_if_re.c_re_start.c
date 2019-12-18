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
struct rl_softc {int dummy; } ;
struct ifnet {struct rl_softc* if_softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  RL_LOCK (struct rl_softc*) ; 
 int /*<<< orphan*/  RL_UNLOCK (struct rl_softc*) ; 
 int /*<<< orphan*/  re_start_locked (struct ifnet*) ; 

__attribute__((used)) static void
re_start(struct ifnet *ifp)
{
	struct rl_softc		*sc;

	sc = ifp->if_softc;
	RL_LOCK(sc);
	re_start_locked(ifp);
	RL_UNLOCK(sc);
}