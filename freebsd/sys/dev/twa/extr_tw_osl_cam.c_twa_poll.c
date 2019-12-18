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
struct twa_softc {int /*<<< orphan*/  ctlr_handle; } ;
struct cam_sim {int dummy; } ;
typedef  int /*<<< orphan*/  TW_VOID ;

/* Variables and functions */
 scalar_t__ cam_sim_softc (struct cam_sim*) ; 
 int /*<<< orphan*/  tw_cl_interrupt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tw_osli_dbg_dprintf (int,struct twa_softc*,char*,struct twa_softc*) ; 

TW_VOID
twa_poll(struct cam_sim *sim)
{
	struct twa_softc *sc = (struct twa_softc *)(cam_sim_softc(sim));

	tw_osli_dbg_dprintf(3, sc, "entering; sc = %p", sc);
	tw_cl_interrupt(&(sc->ctlr_handle));
	tw_osli_dbg_dprintf(3, sc, "exiting; sc = %p", sc);
}