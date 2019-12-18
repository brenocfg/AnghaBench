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
struct nfe_softc {int /*<<< orphan*/  nfe_miibus; } ;
struct mii_data {int dummy; } ;
typedef  int /*<<< orphan*/  if_t ;

/* Variables and functions */
 int /*<<< orphan*/  NFE_LOCK (struct nfe_softc*) ; 
 int /*<<< orphan*/  NFE_UNLOCK (struct nfe_softc*) ; 
 struct mii_data* device_get_softc (int /*<<< orphan*/ ) ; 
 struct nfe_softc* if_getsoftc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mii_mediachg (struct mii_data*) ; 

__attribute__((used)) static int
nfe_ifmedia_upd(if_t ifp)
{
	struct nfe_softc *sc = if_getsoftc(ifp);
	struct mii_data *mii;

	NFE_LOCK(sc);
	mii = device_get_softc(sc->nfe_miibus);
	mii_mediachg(mii);
	NFE_UNLOCK(sc);

	return (0);
}