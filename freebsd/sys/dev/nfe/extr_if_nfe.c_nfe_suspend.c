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
struct nfe_softc {int nfe_suspended; int /*<<< orphan*/  nfe_ifp; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  NFE_LOCK (struct nfe_softc*) ; 
 int /*<<< orphan*/  NFE_UNLOCK (struct nfe_softc*) ; 
 struct nfe_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfe_set_wol (struct nfe_softc*) ; 
 int /*<<< orphan*/  nfe_stop (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nfe_suspend(device_t dev)
{
	struct nfe_softc *sc;

	sc = device_get_softc(dev);

	NFE_LOCK(sc);
	nfe_stop(sc->nfe_ifp);
	nfe_set_wol(sc);
	sc->nfe_suspended = 1;
	NFE_UNLOCK(sc);

	return (0);
}