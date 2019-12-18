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
struct amr_softc {int amr_state; int amr_mailboxphys; int /*<<< orphan*/  amr_hw_lock; TYPE_1__* amr_mailbox; int /*<<< orphan*/  amr_dev; scalar_t__ amr_busyslots; } ;
struct amr_command {int ac_status; int ac_flags; int /*<<< orphan*/  ac_datamap; int /*<<< orphan*/  ac_tag; int /*<<< orphan*/  ac_mailbox; int /*<<< orphan*/ * ac_data; } ;
struct TYPE_2__ {int mb_ident; int mb_nstatus; int mb_status; int mb_poll; int mb_ack; int mb_busy; } ;

/* Variables and functions */
 int AMR_CMD_DATAIN ; 
 int AMR_CMD_DATAOUT ; 
 int /*<<< orphan*/  AMR_MBOX_CMDSIZE ; 
 int AMR_QGET_IDB (struct amr_softc*) ; 
 int AMR_QIDB_ACK ; 
 int AMR_QIDB_SUBMIT ; 
 int /*<<< orphan*/  AMR_QPUT_IDB (struct amr_softc*,int) ; 
 int AMR_STATE_INTEN ; 
 int AMR_STATUS_SUCCESS ; 
 int /*<<< orphan*/  BUS_DMASYNC_POSTREAD ; 
 int /*<<< orphan*/  BUS_DMASYNC_POSTWRITE ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int PCATCH ; 
 int PRIBIO ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  msleep (struct amr_softc*,int /*<<< orphan*/ *,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
amr_quartz_poll_command1(struct amr_softc *sc, struct amr_command *ac)
{
    int count, error;

    mtx_lock(&sc->amr_hw_lock);
    if ((sc->amr_state & AMR_STATE_INTEN) == 0) {
	count=0;
	while (sc->amr_busyslots) {
	    msleep(sc, &sc->amr_hw_lock, PRIBIO | PCATCH, "amrpoll", hz);
	    if(count++>10) {
		break;
	    }
	}

	if(sc->amr_busyslots) {
	    device_printf(sc->amr_dev, "adapter is busy\n");
	    mtx_unlock(&sc->amr_hw_lock);
	    if (ac->ac_data != NULL) {
		bus_dmamap_unload(ac->ac_tag, ac->ac_datamap);
	    }
    	    ac->ac_status=0;
	    return(1);
	}
    }

    bcopy(&ac->ac_mailbox, (void *)(uintptr_t)(volatile void *)sc->amr_mailbox, AMR_MBOX_CMDSIZE);

    /* clear the poll/ack fields in the mailbox */
    sc->amr_mailbox->mb_ident = 0xFE;
    sc->amr_mailbox->mb_nstatus = 0xFF;
    sc->amr_mailbox->mb_status = 0xFF;
    sc->amr_mailbox->mb_poll = 0;
    sc->amr_mailbox->mb_ack = 0;
    sc->amr_mailbox->mb_busy = 1;

    AMR_QPUT_IDB(sc, sc->amr_mailboxphys | AMR_QIDB_SUBMIT);

    while(sc->amr_mailbox->mb_nstatus == 0xFF)
	DELAY(1);
    while(sc->amr_mailbox->mb_status == 0xFF)
	DELAY(1);
    ac->ac_status=sc->amr_mailbox->mb_status;
    error = (ac->ac_status !=AMR_STATUS_SUCCESS) ? 1:0;
    while(sc->amr_mailbox->mb_poll != 0x77)
	DELAY(1);
    sc->amr_mailbox->mb_poll = 0;
    sc->amr_mailbox->mb_ack = 0x77;

    /* acknowledge that we have the commands */
    AMR_QPUT_IDB(sc, sc->amr_mailboxphys | AMR_QIDB_ACK);
    while(AMR_QGET_IDB(sc) & AMR_QIDB_ACK)
	DELAY(1);
    mtx_unlock(&sc->amr_hw_lock);

    /* unmap the command's data buffer */
    if (ac->ac_flags & AMR_CMD_DATAIN) {
	bus_dmamap_sync(ac->ac_tag, ac->ac_datamap, BUS_DMASYNC_POSTREAD);
    }
    if (ac->ac_flags & AMR_CMD_DATAOUT) {
	bus_dmamap_sync(ac->ac_tag, ac->ac_datamap, BUS_DMASYNC_POSTWRITE);
    }
    bus_dmamap_unload(ac->ac_tag, ac->ac_datamap);

    return(error);
}