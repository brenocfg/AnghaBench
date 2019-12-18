#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ flag; int /*<<< orphan*/  data; } ;
union mly_command_packet {TYPE_3__ mmbox; } ;
struct mly_softc {int mly_state; size_t mly_mmbox_command_index; int /*<<< orphan*/  mly_idbr; int /*<<< orphan*/  mly_regs_resource; TYPE_2__* mly_mmbox; int /*<<< orphan*/  mly_command_mailbox; } ;
struct mly_command {TYPE_5__* mc_packet; int /*<<< orphan*/  mc_flags; int /*<<< orphan*/  mc_packetphys; int /*<<< orphan*/  mc_timestamp; int /*<<< orphan*/  mc_slot; struct mly_softc* mc_sc; } ;
struct TYPE_9__ {scalar_t__ flag; int /*<<< orphan*/  data; } ;
struct TYPE_6__ {int /*<<< orphan*/  command_id; } ;
struct TYPE_10__ {TYPE_4__ mmbox; TYPE_1__ generic; } ;
struct TYPE_7__ {union mly_command_packet* mmm_command; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_SPACE_BARRIER_WRITE ; 
 int EBUSY ; 
 int /*<<< orphan*/  MLY_AM_CMDSENT ; 
 int /*<<< orphan*/  MLY_ASSERT_LOCKED (struct mly_softc*) ; 
 int /*<<< orphan*/  MLY_CMD_BUSY ; 
 int /*<<< orphan*/  MLY_HM_CMDSENT ; 
 scalar_t__ MLY_IDBR_TRUE (struct mly_softc*,int /*<<< orphan*/ ) ; 
 int MLY_MMBOX_COMMANDS ; 
 int /*<<< orphan*/  MLY_SET_MBOX (struct mly_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MLY_SET_REG (struct mly_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MLY_STATE_MMBOX_ACTIVE ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bus_barrier (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug_called (int) ; 
 int /*<<< orphan*/  mly_enqueue_busy (struct mly_command*) ; 
 int /*<<< orphan*/  mly_map_command (struct mly_command*) ; 
 int /*<<< orphan*/  time_second ; 

__attribute__((used)) static int
mly_start(struct mly_command *mc)
{
    struct mly_softc		*sc = mc->mc_sc;
    union mly_command_packet	*pkt;

    debug_called(2);
    MLY_ASSERT_LOCKED(sc);

    /* 
     * Set the command up for delivery to the controller. 
     */
    mly_map_command(mc);
    mc->mc_packet->generic.command_id = mc->mc_slot;

#ifdef MLY_DEBUG
    mc->mc_timestamp = time_second;
#endif

    /*
     * Do we have to use the hardware mailbox?
     */
    if (!(sc->mly_state & MLY_STATE_MMBOX_ACTIVE)) {
	/*
	 * Check to see if the controller is ready for us.
	 */
	if (MLY_IDBR_TRUE(sc, MLY_HM_CMDSENT)) {
	    return(EBUSY);
	}
	mc->mc_flags |= MLY_CMD_BUSY;
	
	/*
	 * It's ready, send the command.
	 */
	MLY_SET_MBOX(sc, sc->mly_command_mailbox, &mc->mc_packetphys);
	MLY_SET_REG(sc, sc->mly_idbr, MLY_HM_CMDSENT);

    } else {	/* use memory-mailbox mode */

	pkt = &sc->mly_mmbox->mmm_command[sc->mly_mmbox_command_index];

	/* check to see if the next index is free yet */
	if (pkt->mmbox.flag != 0) {
	    return(EBUSY);
	}
	mc->mc_flags |= MLY_CMD_BUSY;
	
	/* copy in new command */
	bcopy(mc->mc_packet->mmbox.data, pkt->mmbox.data, sizeof(pkt->mmbox.data));
	/* barrier to ensure completion of previous write before we write the flag */
	bus_barrier(sc->mly_regs_resource, 0, 0, BUS_SPACE_BARRIER_WRITE);
	/* copy flag last */
	pkt->mmbox.flag = mc->mc_packet->mmbox.flag;
	/* barrier to ensure completion of previous write before we notify the controller */
	bus_barrier(sc->mly_regs_resource, 0, 0, BUS_SPACE_BARRIER_WRITE);

	/* signal controller, update index */
	MLY_SET_REG(sc, sc->mly_idbr, MLY_AM_CMDSENT);
	sc->mly_mmbox_command_index = (sc->mly_mmbox_command_index + 1) % MLY_MMBOX_COMMANDS;
    }

    mly_enqueue_busy(mc);
    return(0);
}