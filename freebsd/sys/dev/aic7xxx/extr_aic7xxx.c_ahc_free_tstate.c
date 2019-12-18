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
typedef  int u_int ;
struct ahc_tmode_tstate {int dummy; } ;
struct ahc_softc {int our_id_b; int our_id; struct ahc_tmode_tstate** enabled_targets; } ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  free (struct ahc_tmode_tstate*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ahc_free_tstate(struct ahc_softc *ahc, u_int scsi_id, char channel, int force)
{
	struct ahc_tmode_tstate *tstate;

	/*
	 * Don't clean up our "master" tstate.
	 * It has our default user settings.
	 */
	if (((channel == 'B' && scsi_id == ahc->our_id_b)
	  || (channel == 'A' && scsi_id == ahc->our_id))
	 && force == FALSE)
		return;

	if (channel == 'B')
		scsi_id += 8;
	tstate = ahc->enabled_targets[scsi_id];
	if (tstate != NULL)
		free(tstate, M_DEVBUF);
	ahc->enabled_targets[scsi_id] = NULL;
}