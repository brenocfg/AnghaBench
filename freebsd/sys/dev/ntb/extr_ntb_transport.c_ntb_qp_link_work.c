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
typedef  int uint32_t ;
struct ntb_transport_qp {unsigned long long qp_num; int link_is_up; int /*<<< orphan*/  link_work; int /*<<< orphan*/  cb_data; int /*<<< orphan*/  (* event_handler ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;struct ntb_transport_ctx* transport; int /*<<< orphan*/  dev; } ;
struct ntb_transport_ctx {int qp_count; scalar_t__ link_is_up; TYPE_1__* qp_vec; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {scalar_t__ client_ready; } ;

/* Variables and functions */
 int /*<<< orphan*/  NTBT_QP_LINKS ; 
 int NTB_LINK_DOWN_TIMEOUT ; 
 int /*<<< orphan*/  NTB_LINK_UP ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int,void (*) (void*),struct ntb_transport_qp*) ; 
 int hz ; 
 int /*<<< orphan*/  ntb_db_clear_mask (int /*<<< orphan*/ ,unsigned long long) ; 
 int /*<<< orphan*/  ntb_peer_spad_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ntb_printf (int,char*,unsigned long long) ; 
 int /*<<< orphan*/  ntb_spad_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ntb_qp_link_work(void *arg)
{
	struct ntb_transport_qp *qp = arg;
	device_t dev = qp->dev;
	struct ntb_transport_ctx *nt = qp->transport;
	int i;
	uint32_t val;

	/* Report queues that are up on our side */
	for (i = 0, val = 0; i < nt->qp_count; i++) {
		if (nt->qp_vec[i].client_ready)
			val |= (1 << i);
	}
	ntb_peer_spad_write(dev, NTBT_QP_LINKS, val);

	/* See if the remote side is up */
	ntb_spad_read(dev, NTBT_QP_LINKS, &val);
	if ((val & (1ull << qp->qp_num)) != 0) {
		ntb_printf(2, "qp %d link up\n", qp->qp_num);
		qp->link_is_up = true;

		if (qp->event_handler != NULL)
			qp->event_handler(qp->cb_data, NTB_LINK_UP);

		ntb_db_clear_mask(dev, 1ull << qp->qp_num);
	} else if (nt->link_is_up)
		callout_reset(&qp->link_work,
		    NTB_LINK_DOWN_TIMEOUT * hz / 1000, ntb_qp_link_work, qp);
}