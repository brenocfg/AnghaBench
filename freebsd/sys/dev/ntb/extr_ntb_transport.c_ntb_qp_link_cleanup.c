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
struct ntb_transport_qp {int /*<<< orphan*/  cb_data; int /*<<< orphan*/  (* event_handler ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  link_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  NTB_LINK_DOWN ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ntb_qp_link_down_reset (struct ntb_transport_qp*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ntb_qp_link_cleanup(struct ntb_transport_qp *qp)
{

	callout_drain(&qp->link_work);
	ntb_qp_link_down_reset(qp);

	if (qp->event_handler != NULL)
		qp->event_handler(qp->cb_data, NTB_LINK_DOWN);
}