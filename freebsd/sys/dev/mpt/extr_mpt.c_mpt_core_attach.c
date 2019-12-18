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
struct TYPE_4__ {int /*<<< orphan*/  inots; int /*<<< orphan*/  atios; } ;
struct mpt_softc {int failure_id; int /*<<< orphan*/  scsi_tgt_handler_id; TYPE_2__ trt_wildcard; TYPE_1__* trt; int /*<<< orphan*/  request_timeout_list; int /*<<< orphan*/  request_free_list; int /*<<< orphan*/  request_pending_list; int /*<<< orphan*/  ack_frames; } ;
struct TYPE_3__ {int /*<<< orphan*/  inots; int /*<<< orphan*/  atios; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MPT_HANDLER_ID_NONE ; 
 int /*<<< orphan*/  MPT_LOCK (struct mpt_softc*) ; 
 int MPT_MAX_LUNS ; 
 int /*<<< orphan*/  MPT_OFFSET_DOORBELL ; 
 int /*<<< orphan*/  MPT_PRT_DEBUG ; 
 int /*<<< orphan*/  MPT_UNLOCK (struct mpt_softc*) ; 
 int /*<<< orphan*/  STAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int mpt_configure_ioc (struct mpt_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpt_ioc_diag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpt_lprt (struct mpt_softc*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpt_read (struct mpt_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpt_sysctl_attach (struct mpt_softc*) ; 

__attribute__((used)) static int
mpt_core_attach(struct mpt_softc *mpt)
{
        int val, error;

	LIST_INIT(&mpt->ack_frames);
	/* Put all request buffers on the free list */
	TAILQ_INIT(&mpt->request_pending_list);
	TAILQ_INIT(&mpt->request_free_list);
	TAILQ_INIT(&mpt->request_timeout_list);
	for (val = 0; val < MPT_MAX_LUNS; val++) {
		STAILQ_INIT(&mpt->trt[val].atios);
		STAILQ_INIT(&mpt->trt[val].inots);
	}
	STAILQ_INIT(&mpt->trt_wildcard.atios);
	STAILQ_INIT(&mpt->trt_wildcard.inots);
#ifdef	MPT_TEST_MULTIPATH
	mpt->failure_id = -1;
#endif
	mpt->scsi_tgt_handler_id = MPT_HANDLER_ID_NONE;
	mpt_sysctl_attach(mpt);
	mpt_lprt(mpt, MPT_PRT_DEBUG, "doorbell req = %s\n",
	    mpt_ioc_diag(mpt_read(mpt, MPT_OFFSET_DOORBELL)));

	MPT_LOCK(mpt);
	error = mpt_configure_ioc(mpt, 0, 0);
	MPT_UNLOCK(mpt);

	return (error);
}