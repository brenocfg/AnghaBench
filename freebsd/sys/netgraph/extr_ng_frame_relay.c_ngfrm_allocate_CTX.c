#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int ;
struct ctxinfo {int flags; int dlci; } ;
typedef  TYPE_1__* sc_p ;
struct TYPE_3__ {int* ALT; struct ctxinfo* channel; } ;

/* Variables and functions */
 int CHAN_VALID ; 
 int CTX_VALID ; 
 int CTX_VALUE ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int MAX_CT ; 
 int /*<<< orphan*/  bzero (struct ctxinfo*,int) ; 
 int /*<<< orphan*/  log (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int
ngfrm_allocate_CTX(sc_p sc, int dlci)
{
	u_int   ctxnum = -1;	/* what ctx number we are using */
	volatile struct ctxinfo *CTXp = NULL;

	/* Sanity check the dlci value */
	if (dlci > 1023)
		return (-1);

	/* Check to see if we already have an entry for this DLCI */
	if (sc->ALT[dlci]) {
		if ((ctxnum = sc->ALT[dlci] & CTX_VALUE) < MAX_CT) {
			CTXp = sc->channel + ctxnum;
		} else {
			ctxnum = -1;
			sc->ALT[dlci] = 0;	/* paranoid but... */
		}
	}

	/*
	 * If the index has no valid entry yet, then we need to allocate a
	 * CTX number to it
	 */
	if (CTXp == NULL) {
		for (ctxnum = 0; ctxnum < MAX_CT; ctxnum++) {
			/*
			 * If the VALID flag is empty it is unused
			 */
			if ((sc->channel[ctxnum].flags & CHAN_VALID) == 0) {
				bzero(sc->channel + ctxnum,
				      sizeof(struct ctxinfo));
				CTXp = sc->channel + ctxnum;
				sc->ALT[dlci] = ctxnum | CTX_VALID;
				sc->channel[ctxnum].dlci = dlci;
				sc->channel[ctxnum].flags = CHAN_VALID;
				break;
			}
		}
	}

	/*
	 * If we still don't have a CTX pointer, then we never found a free
	 * spot so give up now..
	 */
	if (!CTXp) {
		log(LOG_ERR, "No CTX available for dlci %d\n", dlci);
		return (-1);
	}
	return (ctxnum);
}