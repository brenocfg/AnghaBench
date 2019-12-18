#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct twe_softc {int /*<<< orphan*/  twe_state; int /*<<< orphan*/  twe_buffer_dmat; int /*<<< orphan*/  twe_immediate_map; int /*<<< orphan*/  twe_immediate_dmat; } ;
struct twe_request {int tr_flags; struct twe_softc* tr_sc; int /*<<< orphan*/  tr_dmamap; int /*<<< orphan*/  tr_length; int /*<<< orphan*/  tr_data; int /*<<< orphan*/  tr_realdata; int /*<<< orphan*/  tr_dataphys; } ;
struct TYPE_14__ {int /*<<< orphan*/  ds_addr; } ;
typedef  TYPE_5__ bus_dma_segment_t ;
struct TYPE_13__ {int /*<<< orphan*/ * sgl; } ;
struct TYPE_12__ {int /*<<< orphan*/ * sgl; } ;
struct TYPE_11__ {int /*<<< orphan*/ * sgl; } ;
struct TYPE_10__ {int size; int opcode; int sgl_offset; } ;
struct TYPE_15__ {TYPE_4__ ata; TYPE_3__ io; TYPE_2__ param; TYPE_1__ generic; } ;
typedef  TYPE_6__ TWE_Command ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_PREREAD ; 
 int /*<<< orphan*/  BUS_DMASYNC_PREWRITE ; 
 scalar_t__ EBUSY ; 
 int TWE_CMD_ALIGNBUF ; 
 int TWE_CMD_DATAIN ; 
 int TWE_CMD_DATAOUT ; 
 int TWE_CMD_IMMEDIATE ; 
 int TWE_CMD_IN_PROGRESS ; 
 int TWE_CMD_MAPPED ; 
 TYPE_6__* TWE_FIND_COMMAND (struct twe_request*) ; 
 int /*<<< orphan*/  TWE_MAX_ATA_SGL_LENGTH ; 
 int /*<<< orphan*/  TWE_MAX_SGL_LENGTH ; 
#define  TWE_OP_ATA_PASSTHROUGH 132 
#define  TWE_OP_GET_PARAM 131 
#define  TWE_OP_READ 130 
#define  TWE_OP_SET_PARAM 129 
#define  TWE_OP_WRITE 128 
 int /*<<< orphan*/  TWE_STATE_CTLR_BUSY ; 
 int /*<<< orphan*/  TWE_STATE_FRZN ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug_called (int) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  twe_fillin_sgl (int /*<<< orphan*/ *,TYPE_5__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  twe_requeue_ready (struct twe_request*) ; 
 scalar_t__ twe_start (struct twe_request*) ; 

__attribute__((used)) static void
twe_setup_data_dmamap(void *arg, bus_dma_segment_t *segs, int nsegments, int error)
{
    struct twe_request	*tr = (struct twe_request *)arg;
    struct twe_softc	*sc = tr->tr_sc;
    TWE_Command		*cmd = TWE_FIND_COMMAND(tr);

    debug_called(4);

    if (tr->tr_flags & TWE_CMD_MAPPED)
	panic("already mapped command");

    tr->tr_flags |= TWE_CMD_MAPPED;

    if (tr->tr_flags & TWE_CMD_IN_PROGRESS)
	sc->twe_state &= ~TWE_STATE_FRZN;
    /* save base of first segment in command (applicable if there only one segment) */
    tr->tr_dataphys = segs[0].ds_addr;

    /* correct command size for s/g list size */
    cmd->generic.size += 2 * nsegments;

    /*
     * Due to the fact that parameter and I/O commands have the scatter/gather list in
     * different places, we need to determine which sort of command this actually is
     * before we can populate it correctly.
     */
    switch(cmd->generic.opcode) {
    case TWE_OP_GET_PARAM:
    case TWE_OP_SET_PARAM:
	cmd->generic.sgl_offset = 2;
	twe_fillin_sgl(&cmd->param.sgl[0], segs, nsegments, TWE_MAX_SGL_LENGTH);
	break;
    case TWE_OP_READ:
    case TWE_OP_WRITE:
	cmd->generic.sgl_offset = 3;
	twe_fillin_sgl(&cmd->io.sgl[0], segs, nsegments, TWE_MAX_SGL_LENGTH);
	break;
    case TWE_OP_ATA_PASSTHROUGH:
	cmd->generic.sgl_offset = 5;
	twe_fillin_sgl(&cmd->ata.sgl[0], segs, nsegments, TWE_MAX_ATA_SGL_LENGTH);
	break;
    default:
	/*
	 * Fall back to what the linux driver does.
	 * Do this because the API may send an opcode
	 * the driver knows nothing about and this will
	 * at least stop PCIABRT's from hosing us.
	 */
	switch (cmd->generic.sgl_offset) {
	case 2:
	    twe_fillin_sgl(&cmd->param.sgl[0], segs, nsegments, TWE_MAX_SGL_LENGTH);
	    break;
	case 3:
	    twe_fillin_sgl(&cmd->io.sgl[0], segs, nsegments, TWE_MAX_SGL_LENGTH);
	    break;
	case 5:
	    twe_fillin_sgl(&cmd->ata.sgl[0], segs, nsegments, TWE_MAX_ATA_SGL_LENGTH);
	    break;
	}
    }

    if (tr->tr_flags & TWE_CMD_DATAIN) {
	if (tr->tr_flags & TWE_CMD_IMMEDIATE) {
	    bus_dmamap_sync(sc->twe_immediate_dmat, sc->twe_immediate_map,
			    BUS_DMASYNC_PREREAD);
	} else {
	    bus_dmamap_sync(sc->twe_buffer_dmat, tr->tr_dmamap,
			    BUS_DMASYNC_PREREAD);
	}
    }

    if (tr->tr_flags & TWE_CMD_DATAOUT) {
	/*
	 * if we're using an alignment buffer, and we're writing data
	 * copy the real data out
	 */
	if (tr->tr_flags & TWE_CMD_ALIGNBUF)
	    bcopy(tr->tr_realdata, tr->tr_data, tr->tr_length);

	if (tr->tr_flags & TWE_CMD_IMMEDIATE) {
	    bus_dmamap_sync(sc->twe_immediate_dmat, sc->twe_immediate_map,
			    BUS_DMASYNC_PREWRITE);
	} else {
	    bus_dmamap_sync(sc->twe_buffer_dmat, tr->tr_dmamap,
			    BUS_DMASYNC_PREWRITE);
	}
    }

    if (twe_start(tr) == EBUSY) {
	tr->tr_sc->twe_state |= TWE_STATE_CTLR_BUSY;
	twe_requeue_ready(tr);
    }
}