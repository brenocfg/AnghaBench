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
struct ntb_transport_qp {int /*<<< orphan*/  link_work; } ;
struct ntb_transport_ctx {int qp_count; int qp_bitmap; int /*<<< orphan*/  dev; struct ntb_transport_qp* qp_vec; scalar_t__ link_is_up; int /*<<< orphan*/  link_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ntb_qp_link_cleanup (struct ntb_transport_qp*) ; 
 int /*<<< orphan*/  ntb_spad_clear (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ntb_transport_link_cleanup(struct ntb_transport_ctx *nt)
{
	struct ntb_transport_qp *qp;
	int i;

	callout_drain(&nt->link_work);
	nt->link_is_up = 0;

	/* Pass along the info to any clients */
	for (i = 0; i < nt->qp_count; i++) {
		if ((nt->qp_bitmap & (1 << i)) != 0) {
			qp = &nt->qp_vec[i];
			ntb_qp_link_cleanup(qp);
			callout_drain(&qp->link_work);
		}
	}

	/*
	 * The scratchpad registers keep the values if the remote side
	 * goes down, blast them now to give them a sane value the next
	 * time they are accessed
	 */
	ntb_spad_clear(nt->dev);
}