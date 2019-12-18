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
struct mps_softc {int mps_flags; scalar_t__ io_cmds_active; scalar_t__ io_cmds_highwater; int /*<<< orphan*/  mps_mtx; } ;
struct TYPE_7__ {int /*<<< orphan*/  High; int /*<<< orphan*/  Low; } ;
struct TYPE_6__ {int /*<<< orphan*/  SMID; } ;
struct TYPE_8__ {TYPE_2__ Words; TYPE_1__ Default; } ;
struct mps_command {scalar_t__ cm_state; TYPE_3__ cm_desc; int /*<<< orphan*/  cm_ccb; } ;
struct TYPE_9__ {int /*<<< orphan*/  high; int /*<<< orphan*/  low; } ;
struct TYPE_10__ {TYPE_4__ u; int /*<<< orphan*/  word; } ;
typedef  TYPE_5__ reply_descriptor ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  MPI2_REQUEST_DESCRIPTOR_POST_HIGH_OFFSET ; 
 int /*<<< orphan*/  MPI2_REQUEST_DESCRIPTOR_POST_LOW_OFFSET ; 
 scalar_t__ MPS_CM_STATE_BUSY ; 
 scalar_t__ MPS_CM_STATE_INQUEUE ; 
 int MPS_FLAGS_ATTACH_DONE ; 
 int MPS_FLAGS_SHUTDOWN ; 
 int /*<<< orphan*/  MPS_FUNCTRACE (struct mps_softc*) ; 
 int /*<<< orphan*/  MPS_TRACE ; 
 int /*<<< orphan*/  htole64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mps_dprint (struct mps_softc*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,struct mps_command*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mps_regwrite (struct mps_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mps_enqueue_request(struct mps_softc *sc, struct mps_command *cm)
{
	reply_descriptor rd;
	MPS_FUNCTRACE(sc);
	mps_dprint(sc, MPS_TRACE, "SMID %u cm %p ccb %p\n",
	    cm->cm_desc.Default.SMID, cm, cm->cm_ccb);

	if (sc->mps_flags & MPS_FLAGS_ATTACH_DONE && !(sc->mps_flags & MPS_FLAGS_SHUTDOWN))
		mtx_assert(&sc->mps_mtx, MA_OWNED);

	if (++sc->io_cmds_active > sc->io_cmds_highwater)
		sc->io_cmds_highwater++;
	rd.u.low = cm->cm_desc.Words.Low;
	rd.u.high = cm->cm_desc.Words.High;
	rd.word = htole64(rd.word);

	KASSERT(cm->cm_state == MPS_CM_STATE_BUSY, ("command not busy\n"));
	cm->cm_state = MPS_CM_STATE_INQUEUE;

	/* TODO-We may need to make below regwrite atomic */
	mps_regwrite(sc, MPI2_REQUEST_DESCRIPTOR_POST_LOW_OFFSET,
	    rd.u.low);
	mps_regwrite(sc, MPI2_REQUEST_DESCRIPTOR_POST_HIGH_OFFSET,
	    rd.u.high);
}