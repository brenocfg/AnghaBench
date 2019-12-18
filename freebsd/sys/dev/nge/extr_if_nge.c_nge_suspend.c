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
struct nge_softc {int /*<<< orphan*/  nge_flags; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGE_FLAG_SUSPENDED ; 
 int /*<<< orphan*/  NGE_LOCK (struct nge_softc*) ; 
 int /*<<< orphan*/  NGE_UNLOCK (struct nge_softc*) ; 
 struct nge_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nge_stop (struct nge_softc*) ; 
 int /*<<< orphan*/  nge_wol (struct nge_softc*) ; 

__attribute__((used)) static int
nge_suspend(device_t dev)
{
	struct nge_softc *sc;

	sc = device_get_softc(dev);

	NGE_LOCK(sc);
	nge_stop(sc);
	nge_wol(sc);
	sc->nge_flags |= NGE_FLAG_SUSPENDED;
	NGE_UNLOCK(sc);

	return (0);
}