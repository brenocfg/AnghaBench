#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pfsync_softc {int /*<<< orphan*/  sc_bulk_tmo; scalar_t__ sc_bulk_stateid; scalar_t__ sc_bulk_hashid; int /*<<< orphan*/  sc_ureq_received; } ;
struct TYPE_2__ {scalar_t__ debug; } ;

/* Variables and functions */
 int /*<<< orphan*/  PFSYNC_BLOCK (struct pfsync_softc*) ; 
 int /*<<< orphan*/  PFSYNC_BUNLOCK (struct pfsync_softc*) ; 
 int /*<<< orphan*/  PFSYNC_BUS_START ; 
 scalar_t__ PF_DEBUG_MISC ; 
 TYPE_1__ V_pf_status ; 
 struct pfsync_softc* V_pfsyncif ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct pfsync_softc*) ; 
 int /*<<< orphan*/  pfsync_bulk_status (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfsync_bulk_update ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  time_uptime ; 

__attribute__((used)) static void
pfsync_bulk_start(void)
{
	struct pfsync_softc *sc = V_pfsyncif;

	if (V_pf_status.debug >= PF_DEBUG_MISC)
		printf("pfsync: received bulk update request\n");

	PFSYNC_BLOCK(sc);

	sc->sc_ureq_received = time_uptime;
	sc->sc_bulk_hashid = 0;
	sc->sc_bulk_stateid = 0;
	pfsync_bulk_status(PFSYNC_BUS_START);
	callout_reset(&sc->sc_bulk_tmo, 1, pfsync_bulk_update, sc);
	PFSYNC_BUNLOCK(sc);
}