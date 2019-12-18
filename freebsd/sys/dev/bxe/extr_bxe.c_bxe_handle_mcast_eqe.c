#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ecore_mcast_ramrod_params {TYPE_1__* mcast_obj; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* clear_pending ) (TYPE_2__*) ;} ;
struct TYPE_3__ {scalar_t__ (* check_pending ) (TYPE_1__*) ;TYPE_2__ raw; } ;
struct bxe_softc {TYPE_1__ mcast_obj; } ;
typedef  int /*<<< orphan*/  rparam ;

/* Variables and functions */
 int /*<<< orphan*/  BLOGD (struct bxe_softc*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  BXE_MCAST_LOCK (struct bxe_softc*) ; 
 int /*<<< orphan*/  BXE_MCAST_UNLOCK (struct bxe_softc*) ; 
 int /*<<< orphan*/  DBG_SP ; 
 int /*<<< orphan*/  ECORE_MCAST_CMD_CONT ; 
 int ecore_config_mcast (struct bxe_softc*,struct ecore_mcast_ramrod_params*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ecore_mcast_ramrod_params*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 
 scalar_t__ stub2 (TYPE_1__*) ; 

__attribute__((used)) static void
bxe_handle_mcast_eqe(struct bxe_softc *sc)
{
    struct ecore_mcast_ramrod_params rparam;
    int rc;

    memset(&rparam, 0, sizeof(rparam));

    rparam.mcast_obj = &sc->mcast_obj;

    BXE_MCAST_LOCK(sc);

    /* clear pending state for the last command */
    sc->mcast_obj.raw.clear_pending(&sc->mcast_obj.raw);

    /* if there are pending mcast commands - send them */
    if (sc->mcast_obj.check_pending(&sc->mcast_obj)) {
        rc = ecore_config_mcast(sc, &rparam, ECORE_MCAST_CMD_CONT);
        if (rc < 0) {
            BLOGD(sc, DBG_SP,
                "ERROR: Failed to send pending mcast commands (%d)\n", rc);
        }
    }

    BXE_MCAST_UNLOCK(sc);
}