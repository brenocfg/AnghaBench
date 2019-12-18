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
struct iwi_softc {scalar_t__ fw_state; int /*<<< orphan*/  flags; } ;
struct ieee80211com {struct iwi_softc* ic_softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWI_CMD_ABORT_SCAN ; 
 int /*<<< orphan*/  IWI_FLAG_CHANNEL_SCAN ; 
 scalar_t__ IWI_FW_SCANNING ; 
 int /*<<< orphan*/  IWI_LOCK (struct iwi_softc*) ; 
 int /*<<< orphan*/  IWI_LOCK_DECL ; 
 int /*<<< orphan*/  IWI_UNLOCK (struct iwi_softc*) ; 
 int /*<<< orphan*/  iwi_cmd (struct iwi_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
iwi_scan_end(struct ieee80211com *ic)
{
	struct iwi_softc *sc = ic->ic_softc;
	IWI_LOCK_DECL;

	IWI_LOCK(sc);
	sc->flags &= ~IWI_FLAG_CHANNEL_SCAN;
	/* NB: make sure we're still scanning */
	if (sc->fw_state == IWI_FW_SCANNING)
		iwi_cmd(sc, IWI_CMD_ABORT_SCAN, NULL, 0);
	IWI_UNLOCK(sc);
}