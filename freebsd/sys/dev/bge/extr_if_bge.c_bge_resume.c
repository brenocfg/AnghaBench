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
struct bge_softc {int /*<<< orphan*/  bge_ifp; } ;
typedef  int /*<<< orphan*/  if_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  BGE_LOCK (struct bge_softc*) ; 
 int /*<<< orphan*/  BGE_UNLOCK (struct bge_softc*) ; 
 int IFF_DRV_RUNNING ; 
 int IFF_UP ; 
 int /*<<< orphan*/  bge_init_locked (struct bge_softc*) ; 
 int /*<<< orphan*/  bge_start_locked (int /*<<< orphan*/ ) ; 
 struct bge_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int if_getdrvflags (int /*<<< orphan*/ ) ; 
 int if_getflags (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bge_resume(device_t dev)
{
	struct bge_softc *sc;
	if_t ifp;

	sc = device_get_softc(dev);
	BGE_LOCK(sc);
	ifp = sc->bge_ifp;
	if (if_getflags(ifp) & IFF_UP) {
		bge_init_locked(sc);
		if (if_getdrvflags(ifp) & IFF_DRV_RUNNING)
			bge_start_locked(ifp);
	}
	BGE_UNLOCK(sc);

	return (0);
}