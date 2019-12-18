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
struct nfe_softc {scalar_t__ nfe_suspended; int /*<<< orphan*/  nfe_ifp; } ;
typedef  int /*<<< orphan*/  if_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int IFF_UP ; 
 int /*<<< orphan*/  NFE_LOCK (struct nfe_softc*) ; 
 int /*<<< orphan*/  NFE_UNLOCK (struct nfe_softc*) ; 
 struct nfe_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int if_getflags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfe_init_locked (struct nfe_softc*) ; 
 int /*<<< orphan*/  nfe_power (struct nfe_softc*) ; 

__attribute__((used)) static int
nfe_resume(device_t dev)
{
	struct nfe_softc *sc;
	if_t ifp;

	sc = device_get_softc(dev);

	NFE_LOCK(sc);
	nfe_power(sc);
	ifp = sc->nfe_ifp;
	if (if_getflags(ifp) & IFF_UP)
		nfe_init_locked(sc);
	sc->nfe_suspended = 0;
	NFE_UNLOCK(sc);

	return (0);
}