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
struct mpt_softc {scalar_t__ is_fc; int els_cmds_allocated; TYPE_1__** els_cmd_ptrs; } ;
struct TYPE_6__ {int /*<<< orphan*/  state; } ;
typedef  TYPE_1__ request_t ;

/* Variables and functions */
 int FALSE ; 
 int MPT_MAX_ELS ; 
 int /*<<< orphan*/  MPT_PRT_INFO ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  REQ_STATE_LOCKED ; 
 int TRUE ; 
 int /*<<< orphan*/  free (TYPE_1__**,int /*<<< orphan*/ ) ; 
 TYPE_1__** malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mpt_fc_post_els (struct mpt_softc*,TYPE_1__*,int) ; 
 TYPE_1__* mpt_get_request (struct mpt_softc*,int) ; 
 int /*<<< orphan*/  mpt_lprt (struct mpt_softc*,int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  mpt_prt (struct mpt_softc*,char*) ; 

__attribute__((used)) static int
mpt_add_els_buffers(struct mpt_softc *mpt)
{
	int i;

	if (mpt->is_fc == 0) {
		return (TRUE);
	}

	if (mpt->els_cmds_allocated) {
		return (TRUE);
	}

	mpt->els_cmd_ptrs = malloc(MPT_MAX_ELS * sizeof (request_t *),
	    M_DEVBUF, M_NOWAIT | M_ZERO);

	if (mpt->els_cmd_ptrs == NULL) {
		return (FALSE);
	}

	/*
	 * Feed the chip some ELS buffer resources
	 */
	for (i = 0; i < MPT_MAX_ELS; i++) {
		request_t *req = mpt_get_request(mpt, FALSE);
		if (req == NULL) {
			break;
		}
		req->state |= REQ_STATE_LOCKED;
		mpt->els_cmd_ptrs[i] = req;
		mpt_fc_post_els(mpt, req, i);
	}

	if (i == 0) {
		mpt_prt(mpt, "unable to add ELS buffer resources\n");
		free(mpt->els_cmd_ptrs, M_DEVBUF);
		mpt->els_cmd_ptrs = NULL;
		return (FALSE);
	}
	if (i != MPT_MAX_ELS) {
		mpt_lprt(mpt, MPT_PRT_INFO,
		    "only added %d of %d  ELS buffers\n", i, MPT_MAX_ELS);
	}
	mpt->els_cmds_allocated = i;
	return(TRUE);
}