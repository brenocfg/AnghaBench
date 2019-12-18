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
struct mpt_softc {TYPE_1__* request_pool; } ;
struct TYPE_2__ {int /*<<< orphan*/  callout; } ;
typedef  TYPE_1__ request_t ;

/* Variables and functions */
 int MPT_MAX_REQUESTS (struct mpt_softc*) ; 
 int /*<<< orphan*/  mpt_callout_drain (struct mpt_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mpt_disable_ints (struct mpt_softc*) ; 
 int /*<<< orphan*/  mpt_dma_buf_free (struct mpt_softc*) ; 

__attribute__((used)) static void
mpt_core_detach(struct mpt_softc *mpt)
{
	int val;

	/*
	 * XXX: FREE MEMORY 
	 */
	mpt_disable_ints(mpt);

	/* Make sure no request has pending timeouts. */
	for (val = 0; val < MPT_MAX_REQUESTS(mpt); val++) {
		request_t *req = &mpt->request_pool[val];
		mpt_callout_drain(mpt, &req->callout);
	}

	mpt_dma_buf_free(mpt);
}