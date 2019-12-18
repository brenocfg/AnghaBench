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
typedef  int /*<<< orphan*/  vqs ;
typedef  int /*<<< orphan*/  u8 ;
struct virtchnl_queue_select {int tx_queues; int rx_queues; int /*<<< orphan*/  vsi_id; } ;
struct TYPE_4__ {int num_tx_queues; } ;
struct iavf_sc {TYPE_2__ vsi; TYPE_1__* vsi_res; } ;
struct TYPE_3__ {int /*<<< orphan*/  vsi_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  VIRTCHNL_OP_ENABLE_QUEUES ; 
 int /*<<< orphan*/  iavf_send_pf_msg (struct iavf_sc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

int
iavf_enable_queues(struct iavf_sc *sc)
{
	struct virtchnl_queue_select vqs;

	vqs.vsi_id = sc->vsi_res->vsi_id;
	/* XXX: In Linux PF, as long as neither of these is 0,
	 * every queue in VF VSI is enabled. */
	vqs.tx_queues = (1 << sc->vsi.num_tx_queues) - 1;
	vqs.rx_queues = vqs.tx_queues;
	iavf_send_pf_msg(sc, VIRTCHNL_OP_ENABLE_QUEUES,
			   (u8 *)&vqs, sizeof(vqs));
	return (0);
}