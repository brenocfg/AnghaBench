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
struct rl_softc {int /*<<< orphan*/  rl_miibus; } ;
struct mii_data {int dummy; } ;
struct ifnet {struct rl_softc* if_softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  RL_LOCK (struct rl_softc*) ; 
 int /*<<< orphan*/  RL_UNLOCK (struct rl_softc*) ; 
 struct mii_data* device_get_softc (int /*<<< orphan*/ ) ; 
 int mii_mediachg (struct mii_data*) ; 

__attribute__((used)) static int
re_ifmedia_upd(struct ifnet *ifp)
{
	struct rl_softc		*sc;
	struct mii_data		*mii;
	int			error;

	sc = ifp->if_softc;
	mii = device_get_softc(sc->rl_miibus);
	RL_LOCK(sc);
	error = mii_mediachg(mii);
	RL_UNLOCK(sc);

	return (error);
}