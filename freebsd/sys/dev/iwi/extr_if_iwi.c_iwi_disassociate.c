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
struct iwi_associate {int /*<<< orphan*/  chan; int /*<<< orphan*/  bssid; int /*<<< orphan*/  type; } ;
struct iwi_softc {int flags; struct iwi_associate assoc; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int /*<<< orphan*/  IWI_CMD_ASSOCIATE ; 
 int IWI_FLAG_ASSOCIATED ; 
 int /*<<< orphan*/  IWI_FW_DISASSOCIATING ; 
 int /*<<< orphan*/  IWI_HC_DISASSOC ; 
 int /*<<< orphan*/  IWI_HC_DISASSOC_QUIET ; 
 int /*<<< orphan*/  IWI_STATE_BEGIN (struct iwi_softc*,int /*<<< orphan*/ ) ; 
 int iwi_cmd (struct iwi_softc*,int /*<<< orphan*/ ,struct iwi_associate*,int) ; 

__attribute__((used)) static int
iwi_disassociate(struct iwi_softc *sc, int quiet)
{
	struct iwi_associate *assoc = &sc->assoc;

	if ((sc->flags & IWI_FLAG_ASSOCIATED) == 0) {
		DPRINTF(("Not associated\n"));
		return (-1);
	}

	IWI_STATE_BEGIN(sc, IWI_FW_DISASSOCIATING);

	if (quiet)
		assoc->type = IWI_HC_DISASSOC_QUIET;
	else
		assoc->type = IWI_HC_DISASSOC;

	DPRINTF(("Trying to disassociate from %6D channel %u\n",
	    assoc->bssid, ":", assoc->chan));
	return iwi_cmd(sc, IWI_CMD_ASSOCIATE, assoc, sizeof *assoc);
}