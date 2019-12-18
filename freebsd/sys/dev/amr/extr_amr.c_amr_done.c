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
struct amr_softc {int /*<<< orphan*/  amr_dev; struct amr_command** amr_busycmd; scalar_t__ (* amr_get_work ) (struct amr_softc*,struct amr_mailbox*) ;} ;
struct amr_mailbox {int mb_nstatus; int* mb_completed; int /*<<< orphan*/  mb_status; } ;
struct amr_command {int /*<<< orphan*/  ac_status; } ;
typedef  int /*<<< orphan*/  ac_qhead_t ;

/* Variables and functions */
 int /*<<< orphan*/  amr_complete (struct amr_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  amr_enqueue_completed (struct amr_command*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  amr_freeslot (struct amr_command*) ; 
 int /*<<< orphan*/  amr_init_qhead (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debug (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug_called (int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ stub1 (struct amr_softc*,struct amr_mailbox*) ; 

int
amr_done(struct amr_softc *sc)
{
    ac_qhead_t		head;
    struct amr_command	*ac;
    struct amr_mailbox	mbox;
    int			i, idx, result;
    
    debug_called(3);

    /* See if there's anything for us to do */
    result = 0;
    amr_init_qhead(&head);

    /* loop collecting completed commands */
    for (;;) {
	/* poll for a completed command's identifier and status */
	if (sc->amr_get_work(sc, &mbox)) {
	    result = 1;
	    
	    /* iterate over completed commands in this result */
	    for (i = 0; i < mbox.mb_nstatus; i++) {
		/* get pointer to busy command */
		idx = mbox.mb_completed[i] - 1;
		ac = sc->amr_busycmd[idx];

		/* really a busy command? */
		if (ac != NULL) {

		    /* pull the command from the busy index */
		    amr_freeslot(ac);
		
		    /* save status for later use */
		    ac->ac_status = mbox.mb_status;
		    amr_enqueue_completed(ac, &head);
		    debug(3, "completed command with status %x", mbox.mb_status);
		} else {
		    device_printf(sc->amr_dev, "bad slot %d completed\n", idx);
		}
	    }
	} else
	    break;	/* no work */
    }

    /* handle completion and timeouts */
    amr_complete(sc, &head);

    return(result);
}