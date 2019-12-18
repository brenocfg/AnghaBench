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
struct msk_if_softc {int /*<<< orphan*/  msk_miibus; } ;
struct mii_data {int dummy; } ;
struct ifnet {struct msk_if_softc* if_softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSK_IF_LOCK (struct msk_if_softc*) ; 
 int /*<<< orphan*/  MSK_IF_UNLOCK (struct msk_if_softc*) ; 
 struct mii_data* device_get_softc (int /*<<< orphan*/ ) ; 
 int mii_mediachg (struct mii_data*) ; 

__attribute__((used)) static int
msk_mediachange(struct ifnet *ifp)
{
	struct msk_if_softc *sc_if;
	struct mii_data	*mii;
	int error;

	sc_if = ifp->if_softc;

	MSK_IF_LOCK(sc_if);
	mii = device_get_softc(sc_if->msk_miibus);
	error = mii_mediachg(mii);
	MSK_IF_UNLOCK(sc_if);

	return (error);
}