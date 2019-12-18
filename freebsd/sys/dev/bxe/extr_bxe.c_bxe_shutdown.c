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
struct bxe_softc {scalar_t__ state; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  BLOGD (struct bxe_softc*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  BXE_CORE_LOCK (struct bxe_softc*) ; 
 int /*<<< orphan*/  BXE_CORE_UNLOCK (struct bxe_softc*) ; 
 scalar_t__ BXE_STATE_CLOSED ; 
 int /*<<< orphan*/  DBG_LOAD ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  UNLOAD_NORMAL ; 
 int /*<<< orphan*/  bxe_nic_unload (struct bxe_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bxe_periodic_stop (struct bxe_softc*) ; 
 struct bxe_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bxe_shutdown(device_t dev)
{
    struct bxe_softc *sc;

    sc = device_get_softc(dev);

    BLOGD(sc, DBG_LOAD, "Starting shutdown...\n");

    /* stop the periodic callout */
    bxe_periodic_stop(sc);

    if (sc->state != BXE_STATE_CLOSED) {
    	BXE_CORE_LOCK(sc);
    	bxe_nic_unload(sc, UNLOAD_NORMAL, FALSE);
    	BXE_CORE_UNLOCK(sc);
    }

    return (0);
}