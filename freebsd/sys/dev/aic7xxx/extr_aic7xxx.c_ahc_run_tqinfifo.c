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
struct target_cmd {scalar_t__ cmd_valid; } ;
struct ahc_softc {int features; size_t tqinfifonext; int /*<<< orphan*/  shared_data_dmamap; int /*<<< orphan*/  shared_data_dmat; struct target_cmd* targetcmds; } ;

/* Variables and functions */
 int AHC_AUTOPAUSE ; 
 int AHC_HS_MAILBOX ; 
 int /*<<< orphan*/  BUS_DMASYNC_POSTREAD ; 
 int /*<<< orphan*/  BUS_DMASYNC_PREREAD ; 
 int HOST_TQINPOS ; 
 int /*<<< orphan*/  HS_MAILBOX ; 
 int /*<<< orphan*/  KERNEL_TQINPOS ; 
 int TRUE ; 
 scalar_t__ ahc_handle_target_cmd (struct ahc_softc*,struct target_cmd*) ; 
 int ahc_inb (struct ahc_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahc_outb (struct ahc_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ahc_pause (struct ahc_softc*) ; 
 int /*<<< orphan*/  ahc_sync_tqinfifo (struct ahc_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahc_targetcmd_offset (struct ahc_softc*,size_t) ; 
 int /*<<< orphan*/  ahc_unpause (struct ahc_softc*) ; 
 int /*<<< orphan*/  aic_dmamap_sync (struct ahc_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

void
ahc_run_tqinfifo(struct ahc_softc *ahc, int paused)
{
	struct target_cmd *cmd;

	/*
	 * If the card supports auto-access pause,
	 * we can access the card directly regardless
	 * of whether it is paused or not.
	 */
	if ((ahc->features & AHC_AUTOPAUSE) != 0)
		paused = TRUE;

	ahc_sync_tqinfifo(ahc, BUS_DMASYNC_POSTREAD);
	while ((cmd = &ahc->targetcmds[ahc->tqinfifonext])->cmd_valid != 0) {

		/*
		 * Only advance through the queue if we
		 * have the resources to process the command.
		 */
		if (ahc_handle_target_cmd(ahc, cmd) != 0)
			break;

		cmd->cmd_valid = 0;
		aic_dmamap_sync(ahc, ahc->shared_data_dmat,
				ahc->shared_data_dmamap,
				ahc_targetcmd_offset(ahc, ahc->tqinfifonext),
				sizeof(struct target_cmd),
				BUS_DMASYNC_PREREAD);
		ahc->tqinfifonext++;

		/*
		 * Lazily update our position in the target mode incoming
		 * command queue as seen by the sequencer.
		 */
		if ((ahc->tqinfifonext & (HOST_TQINPOS - 1)) == 1) {
			if ((ahc->features & AHC_HS_MAILBOX) != 0) {
				u_int hs_mailbox;

				hs_mailbox = ahc_inb(ahc, HS_MAILBOX);
				hs_mailbox &= ~HOST_TQINPOS;
				hs_mailbox |= ahc->tqinfifonext & HOST_TQINPOS;
				ahc_outb(ahc, HS_MAILBOX, hs_mailbox);
			} else {
				if (!paused)
					ahc_pause(ahc);	
				ahc_outb(ahc, KERNEL_TQINPOS,
					 ahc->tqinfifonext & HOST_TQINPOS);
				if (!paused)
					ahc_unpause(ahc);
			}
		}
	}
}