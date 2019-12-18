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
struct amr_softc {scalar_t__ (* amr_submit_command ) (struct amr_command*) ;int /*<<< orphan*/  amr_state; int /*<<< orphan*/  amr_buffer_dmat; int /*<<< orphan*/  amr_buffer64_dmat; } ;
struct amr_command {int ac_flags; int /*<<< orphan*/  ac_length; int /*<<< orphan*/ * ac_data; int /*<<< orphan*/  ac_datamap; int /*<<< orphan*/  ac_tag; int /*<<< orphan*/  ac_dmamap; int /*<<< orphan*/  ac_dma64map; struct amr_softc* ac_sc; } ;
typedef  int /*<<< orphan*/  bus_dmamap_callback_t ;

/* Variables and functions */
 scalar_t__ AC_IS_SG64 (struct amr_command*) ; 
 int AMR_CMD_CCB ; 
 int AMR_CMD_MAPPED ; 
 int /*<<< orphan*/  AMR_STATE_QUEUE_FRZN ; 
 scalar_t__ EBUSY ; 
 scalar_t__ EINPROGRESS ; 
 int /*<<< orphan*/  amr_freeslot (struct amr_command*) ; 
 int /*<<< orphan*/  amr_requeue_ready (struct amr_command*) ; 
 int /*<<< orphan*/ * amr_setup_ccb ; 
 int /*<<< orphan*/ * amr_setup_data ; 
 scalar_t__ bus_dmamap_load (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct amr_command*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug_called (int) ; 
 scalar_t__ stub1 (struct amr_command*) ; 

__attribute__((used)) static int
amr_mapcmd(struct amr_command *ac)
{
    bus_dmamap_callback_t *cb;
    struct amr_softc	*sc = ac->ac_sc;

    debug_called(3);

    if (AC_IS_SG64(ac)) {
	ac->ac_tag = sc->amr_buffer64_dmat;
	ac->ac_datamap = ac->ac_dma64map;
    } else {
	ac->ac_tag = sc->amr_buffer_dmat;
	ac->ac_datamap = ac->ac_dmamap;
    }

    if (ac->ac_flags & AMR_CMD_CCB)
	cb = amr_setup_ccb;
    else
	cb = amr_setup_data;

    /* if the command involves data at all, and hasn't been mapped */
    if ((ac->ac_flags & AMR_CMD_MAPPED) == 0 && (ac->ac_data != NULL)) {
	/* map the data buffers into bus space and build the s/g list */
	if (bus_dmamap_load(ac->ac_tag, ac->ac_datamap, ac->ac_data,
	     ac->ac_length, cb, ac, 0) == EINPROGRESS) {
	    sc->amr_state |= AMR_STATE_QUEUE_FRZN;
	}
   } else {
    	if (sc->amr_submit_command(ac) == EBUSY) {
	    amr_freeslot(ac);
	    amr_requeue_ready(ac);
	}
   }

    return (0);
}