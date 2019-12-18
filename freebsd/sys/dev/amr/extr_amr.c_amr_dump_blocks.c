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
typedef  int /*<<< orphan*/  u_int32_t ;
struct amr_softc {int /*<<< orphan*/  amr_state; scalar_t__ (* amr_poll_command ) (struct amr_command*) ;} ;
struct TYPE_2__ {int mb_blkcount; int mb_drive; int /*<<< orphan*/  mb_lba; int /*<<< orphan*/  mb_command; } ;
struct amr_command {int ac_flags; int ac_length; int ac_status; TYPE_1__ ac_mailbox; void* ac_data; } ;

/* Variables and functions */
 int AMR_BLKSIZE ; 
 int AMR_CMD_DATAOUT ; 
 int /*<<< orphan*/  AMR_CMD_LWRITE ; 
 int AMR_CMD_PRIORITY ; 
 int /*<<< orphan*/  AMR_STATE_INTEN ; 
 int EIO ; 
 struct amr_command* amr_alloccmd (struct amr_softc*) ; 
 int /*<<< orphan*/  amr_releasecmd (struct amr_command*) ; 
 int /*<<< orphan*/  debug_called (int) ; 
 scalar_t__ stub1 (struct amr_command*) ; 

int
amr_dump_blocks(struct amr_softc *sc, int unit, u_int32_t lba, void *data, int blks)
{
    struct amr_command	*ac;
    int			error = EIO;

    debug_called(1);

    sc->amr_state |= AMR_STATE_INTEN;

    /* get ourselves a command buffer */
    if ((ac = amr_alloccmd(sc)) == NULL)
	goto out;
    /* set command flags */
    ac->ac_flags |= AMR_CMD_PRIORITY | AMR_CMD_DATAOUT;
    
    /* point the command at our data */
    ac->ac_data = data;
    ac->ac_length = blks * AMR_BLKSIZE;
    
    /* build the command proper */
    ac->ac_mailbox.mb_command 	= AMR_CMD_LWRITE;
    ac->ac_mailbox.mb_blkcount	= blks;
    ac->ac_mailbox.mb_lba	= lba;
    ac->ac_mailbox.mb_drive	= unit;

    /* can't assume that interrupts are going to work here, so play it safe */
    if (sc->amr_poll_command(ac))
	goto out;
    error = ac->ac_status;
    
 out:
    if (ac != NULL)
	amr_releasecmd(ac);

    sc->amr_state &= ~AMR_STATE_INTEN;
    return (error);
}