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
struct ecore_mcast_ramrod_params {int /*<<< orphan*/ * mcast_obj; int /*<<< orphan*/ * member_0; } ;
struct bxe_softc {int /*<<< orphan*/  mcast_obj; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLOGE (struct bxe_softc*,char*,int) ; 
 int /*<<< orphan*/  BXE_MCAST_LOCK (struct bxe_softc*) ; 
 int /*<<< orphan*/  BXE_MCAST_UNLOCK (struct bxe_softc*) ; 
 int /*<<< orphan*/  ECORE_MCAST_CMD_ADD ; 
 int /*<<< orphan*/  ECORE_MCAST_CMD_DEL ; 
 int /*<<< orphan*/  bxe_free_mcast_macs_list (struct ecore_mcast_ramrod_params*) ; 
 int bxe_init_mcast_macs_list (struct bxe_softc*,struct ecore_mcast_ramrod_params*) ; 
 int ecore_config_mcast (struct bxe_softc*,struct ecore_mcast_ramrod_params*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bxe_set_mc_list(struct bxe_softc *sc)
{
    struct ecore_mcast_ramrod_params rparam = { NULL };
    int rc = 0;

    rparam.mcast_obj = &sc->mcast_obj;

    BXE_MCAST_LOCK(sc);

    /* first, clear all configured multicast MACs */
    rc = ecore_config_mcast(sc, &rparam, ECORE_MCAST_CMD_DEL);
    if (rc < 0) {
        BLOGE(sc, "Failed to clear multicast configuration: %d\n", rc);
        /* Manual backport parts of FreeBSD upstream r284470. */
        BXE_MCAST_UNLOCK(sc);
        return (rc);
    }

    /* configure a new MACs list */
    rc = bxe_init_mcast_macs_list(sc, &rparam);
    if (rc) {
        BLOGE(sc, "Failed to create mcast MACs list (%d)\n", rc);
        BXE_MCAST_UNLOCK(sc);
        return (rc);
    }

    /* Now add the new MACs */
    rc = ecore_config_mcast(sc, &rparam, ECORE_MCAST_CMD_ADD);
    if (rc < 0) {
        BLOGE(sc, "Failed to set new mcast config (%d)\n", rc);
    }

    bxe_free_mcast_macs_list(&rparam);

    BXE_MCAST_UNLOCK(sc);

    return (rc);
}