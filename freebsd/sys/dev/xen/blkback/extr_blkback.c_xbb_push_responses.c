#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ rsp_prod_pvt; scalar_t__ req_cons; } ;
struct TYPE_5__ {TYPE_2__ common; } ;
struct xbb_softc {scalar_t__ reqs_queued_for_completion; int /*<<< orphan*/  reqs_completed; TYPE_1__ rings; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  RING_FINAL_CHECK_FOR_REQUESTS (TYPE_2__*,int) ; 
 scalar_t__ RING_HAS_UNCONSUMED_REQUESTS (TYPE_2__*) ; 
 int /*<<< orphan*/  RING_PUSH_RESPONSES_AND_CHECK_NOTIFY (TYPE_2__*,int) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
xbb_push_responses(struct xbb_softc *xbb, int *run_taskqueue, int *notify)
{
	int more_to_do;

	/*
	 * The mutex is required here.
	 */
	mtx_assert(&xbb->lock, MA_OWNED);

	more_to_do = 0;

	RING_PUSH_RESPONSES_AND_CHECK_NOTIFY(&xbb->rings.common, *notify);

	if (xbb->rings.common.rsp_prod_pvt == xbb->rings.common.req_cons) {

		/*
		 * Tail check for pending requests. Allows frontend to avoid
		 * notifications if requests are already in flight (lower
		 * overheads and promotes batching).
		 */
		RING_FINAL_CHECK_FOR_REQUESTS(&xbb->rings.common, more_to_do);
	} else if (RING_HAS_UNCONSUMED_REQUESTS(&xbb->rings.common)) {

		more_to_do = 1;
	}

	xbb->reqs_completed += xbb->reqs_queued_for_completion;
	xbb->reqs_queued_for_completion = 0;

	*run_taskqueue = more_to_do;
}