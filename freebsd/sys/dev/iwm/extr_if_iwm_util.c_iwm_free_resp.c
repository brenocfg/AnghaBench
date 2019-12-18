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
struct iwm_softc {int sc_wantresp; } ;
struct iwm_host_cmd {int flags; } ;

/* Variables and functions */
 int IWM_CMD_SYNC ; 
 int IWM_CMD_WANT_SKB ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  wakeup (int*) ; 

void
iwm_free_resp(struct iwm_softc *sc, struct iwm_host_cmd *hcmd)
{
	KASSERT(sc->sc_wantresp != -1, ("already freed"));
	KASSERT((hcmd->flags & (IWM_CMD_WANT_SKB|IWM_CMD_SYNC))
	    == (IWM_CMD_WANT_SKB|IWM_CMD_SYNC), ("invalid flags"));
	sc->sc_wantresp = -1;
	wakeup(&sc->sc_wantresp);
}