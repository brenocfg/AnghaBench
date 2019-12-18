#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int32_t ;
struct aac_softc {int /*<<< orphan*/  aac_ev_cmfree; int /*<<< orphan*/  aac_max_fib_size; int /*<<< orphan*/  aac_io_lock; } ;
struct aac_event {int /*<<< orphan*/  ev_arg; int /*<<< orphan*/  (* ev_callback ) (struct aac_softc*,struct aac_event*,int /*<<< orphan*/ ) ;} ;
struct aac_command {TYPE_3__* cm_fib; scalar_t__ cm_fibphys; struct aac_softc* cm_sc; scalar_t__ cm_passthr_dmat; int /*<<< orphan*/ * cm_ccb; int /*<<< orphan*/ * cm_complete; scalar_t__ cm_flags; int /*<<< orphan*/ * cm_sgtable; } ;
struct TYPE_4__ {scalar_t__ ReceiverFibAddress; } ;
struct TYPE_5__ {scalar_t__ Handle; TYPE_1__ u; int /*<<< orphan*/  SenderSize; scalar_t__ Unused; int /*<<< orphan*/  StructType; int /*<<< orphan*/  XferState; } ;
struct TYPE_6__ {TYPE_2__ Header; } ;

/* Variables and functions */
 int /*<<< orphan*/  AAC_FIBSTATE_EMPTY ; 
 int /*<<< orphan*/  AAC_FIBTYPE_TFIB ; 
 char* HBA_FLAGS_DBG_FUNCTION_ENTRY_B ; 
 int /*<<< orphan*/  MA_OWNED ; 
 struct aac_event* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct aac_event*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aac_enqueue_free (struct aac_command*) ; 
 int /*<<< orphan*/  ev_links ; 
 int /*<<< orphan*/  fwprintf (struct aac_softc*,char*,char*) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct aac_softc*,struct aac_event*,int /*<<< orphan*/ ) ; 

void
aacraid_release_command(struct aac_command *cm)
{
	struct aac_event *event;
	struct aac_softc *sc;

	sc = cm->cm_sc;
	fwprintf(sc, HBA_FLAGS_DBG_FUNCTION_ENTRY_B, "");
	mtx_assert(&sc->aac_io_lock, MA_OWNED);

	/* (re)initialize the command/FIB */
	cm->cm_sgtable = NULL;
	cm->cm_flags = 0;
	cm->cm_complete = NULL;
	cm->cm_ccb = NULL;
	cm->cm_passthr_dmat = 0;
	cm->cm_fib->Header.XferState = AAC_FIBSTATE_EMPTY;
	cm->cm_fib->Header.StructType = AAC_FIBTYPE_TFIB;
	cm->cm_fib->Header.Unused = 0;
	cm->cm_fib->Header.SenderSize = cm->cm_sc->aac_max_fib_size;

	/*
	 * These are duplicated in aac_start to cover the case where an
	 * intermediate stage may have destroyed them.  They're left
	 * initialized here for debugging purposes only.
	 */
	cm->cm_fib->Header.u.ReceiverFibAddress = (u_int32_t)cm->cm_fibphys;
	cm->cm_fib->Header.Handle = 0;

	aac_enqueue_free(cm);

	/*
	 * Dequeue all events so that there's no risk of events getting
	 * stranded.
	 */
	while ((event = TAILQ_FIRST(&sc->aac_ev_cmfree)) != NULL) {
		TAILQ_REMOVE(&sc->aac_ev_cmfree, event, ev_links);
		event->ev_callback(sc, event, event->ev_arg);
	}
}