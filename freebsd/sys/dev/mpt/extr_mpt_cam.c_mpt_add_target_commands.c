#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct mpt_softc {int mpt_max_tgtcmds; int tgt_cmds_allocated; TYPE_1__** tgt_cmd_ptrs; } ;
struct TYPE_6__ {int /*<<< orphan*/  state; } ;
typedef  TYPE_1__ request_t ;

/* Variables and functions */
 int FALSE ; 
 int MPT_MAX_REQUESTS (struct mpt_softc*) ; 
 int /*<<< orphan*/  MPT_PRT_ERROR ; 
 int /*<<< orphan*/  MPT_PRT_INFO ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  REQ_STATE_LOCKED ; 
 int TRUE ; 
 int /*<<< orphan*/  free (TYPE_1__**,int /*<<< orphan*/ ) ; 
 TYPE_1__** malloc (int,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* mpt_get_request (struct mpt_softc*,int) ; 
 int /*<<< orphan*/  mpt_lprt (struct mpt_softc*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  mpt_post_target_command (struct mpt_softc*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  mpt_prt (struct mpt_softc*,char*) ; 

__attribute__((used)) static int
mpt_add_target_commands(struct mpt_softc *mpt)
{
	int i, max;

	if (mpt->tgt_cmd_ptrs) {
		return (TRUE);
	}

	max = MPT_MAX_REQUESTS(mpt) >> 1;
	if (max > mpt->mpt_max_tgtcmds) {
		max = mpt->mpt_max_tgtcmds;
	}
	mpt->tgt_cmd_ptrs =
	    malloc(max * sizeof (request_t *), M_DEVBUF, M_NOWAIT | M_ZERO);
	if (mpt->tgt_cmd_ptrs == NULL) {
		mpt_prt(mpt,
		    "mpt_add_target_commands: could not allocate cmd ptrs\n");
		return (FALSE);
	}

	for (i = 0; i < max; i++) {
		request_t *req;

		req = mpt_get_request(mpt, FALSE);
		if (req == NULL) {
			break;
		}
		req->state |= REQ_STATE_LOCKED;
		mpt->tgt_cmd_ptrs[i] = req;
		mpt_post_target_command(mpt, req, i);
	}


	if (i == 0) {
		mpt_lprt(mpt, MPT_PRT_ERROR, "could not add any target bufs\n");
		free(mpt->tgt_cmd_ptrs, M_DEVBUF);
		mpt->tgt_cmd_ptrs = NULL;
		return (FALSE);
	}

	mpt->tgt_cmds_allocated = i;

	if (i < max) {
		mpt_lprt(mpt, MPT_PRT_INFO,
		    "added %d of %d target bufs\n", i, max);
	}
	return (i);
}