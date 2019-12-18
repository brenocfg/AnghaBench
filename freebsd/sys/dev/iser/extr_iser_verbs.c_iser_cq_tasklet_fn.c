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
struct iser_comp {struct ib_wc* wcs; struct ib_cq* cq; } ;
struct ib_wc {int dummy; } ;
struct ib_cq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (struct ib_wc*) ; 
 int /*<<< orphan*/  IB_CQ_NEXT_COMP ; 
 int ib_poll_cq (struct ib_cq*,int /*<<< orphan*/ ,struct ib_wc* const) ; 
 int /*<<< orphan*/  ib_req_notify_cq (struct ib_cq*,int /*<<< orphan*/ ) ; 
 int iser_cq_poll_limit ; 
 int /*<<< orphan*/  iser_handle_wc (struct ib_wc*) ; 

__attribute__((used)) static void
iser_cq_tasklet_fn(void *data, int pending)
{
	struct iser_comp *comp = (struct iser_comp *)data;
	struct ib_cq *cq = comp->cq;
	struct ib_wc *const wcs = comp->wcs;
	int completed = 0;
	int i;
	int n;

	while ((n = ib_poll_cq(cq, ARRAY_SIZE(comp->wcs), wcs)) > 0) {
		for (i = 0; i < n; i++)
			iser_handle_wc(&wcs[i]);

		completed += n;
		if (completed >= iser_cq_poll_limit)
			break;
	}

	/*
	 * It is assumed here that arming CQ only once its empty
	 * would not cause interrupts to be missed.
	 */
	ib_req_notify_cq(cq, IB_CQ_NEXT_COMP);
}