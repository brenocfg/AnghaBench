#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ evt_class; int locale; } ;
union mfi_evt {int word; TYPE_1__ members; } ;
typedef  int uint32_t ;
struct mfi_softc {int last_seq_num; struct mfi_command* mfi_aen_cm; int /*<<< orphan*/  mfi_io_lock; } ;
struct mfi_evt_detail {int dummy; } ;
struct mfi_dcmd_frame {int /*<<< orphan*/  mbox; } ;
struct mfi_command {int /*<<< orphan*/  cm_complete; int /*<<< orphan*/  cm_flags; TYPE_2__* cm_frame; } ;
struct TYPE_4__ {struct mfi_dcmd_frame dcmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  MFI_CMD_DATAIN ; 
 int /*<<< orphan*/  MFI_DCMD_CTRL_EVENT_WAIT ; 
 int /*<<< orphan*/  mfi_abort (struct mfi_softc*,struct mfi_command**) ; 
 int /*<<< orphan*/  mfi_aen_complete ; 
 int mfi_dcmd_command (struct mfi_softc*,struct mfi_command**,int /*<<< orphan*/ ,void**,int) ; 
 int /*<<< orphan*/  mfi_enqueue_ready (struct mfi_command*) ; 
 int /*<<< orphan*/  mfi_startio (struct mfi_softc*) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mfi_aen_register(struct mfi_softc *sc, int seq, int locale)
{
	struct mfi_command *cm;
	struct mfi_dcmd_frame *dcmd;
	union mfi_evt current_aen, prior_aen;
	struct mfi_evt_detail *ed = NULL;
	int error = 0;

	mtx_assert(&sc->mfi_io_lock, MA_OWNED);

	current_aen.word = locale;
	if (sc->mfi_aen_cm != NULL) {
		prior_aen.word =
		    ((uint32_t *)&sc->mfi_aen_cm->cm_frame->dcmd.mbox)[1];
		if (prior_aen.members.evt_class <= current_aen.members.evt_class &&
		    !((prior_aen.members.locale & current_aen.members.locale)
		    ^current_aen.members.locale)) {
			return (0);
		} else {
			prior_aen.members.locale |= current_aen.members.locale;
			if (prior_aen.members.evt_class
			    < current_aen.members.evt_class)
				current_aen.members.evt_class =
				    prior_aen.members.evt_class;
			mfi_abort(sc, &sc->mfi_aen_cm);
		}
	}

	error = mfi_dcmd_command(sc, &cm, MFI_DCMD_CTRL_EVENT_WAIT,
	    (void **)&ed, sizeof(*ed));
	if (error)
		goto out;

	dcmd = &cm->cm_frame->dcmd;
	((uint32_t *)&dcmd->mbox)[0] = seq;
	((uint32_t *)&dcmd->mbox)[1] = locale;
	cm->cm_flags = MFI_CMD_DATAIN;
	cm->cm_complete = mfi_aen_complete;

	sc->last_seq_num = seq;
	sc->mfi_aen_cm = cm;

	mfi_enqueue_ready(cm);
	mfi_startio(sc);

out:
	return (error);
}