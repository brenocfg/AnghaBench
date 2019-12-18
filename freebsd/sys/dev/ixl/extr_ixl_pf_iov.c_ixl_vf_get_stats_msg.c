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
typedef  int uint16_t ;
struct virtchnl_queue_select {scalar_t__ vsi_id; } ;
struct TYPE_2__ {scalar_t__ vsi_num; int /*<<< orphan*/  eth_stats; } ;
struct ixl_vf {TYPE_1__ vsi; } ;
struct ixl_pf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  I40E_ERR_PARAM ; 
 int /*<<< orphan*/  I40E_SUCCESS ; 
 int /*<<< orphan*/  VIRTCHNL_OP_GET_STATS ; 
 int /*<<< orphan*/  i40e_send_vf_nack (struct ixl_pf*,struct ixl_vf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixl_send_vf_msg (struct ixl_pf*,struct ixl_vf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ixl_update_eth_stats (TYPE_1__*) ; 

__attribute__((used)) static void
ixl_vf_get_stats_msg(struct ixl_pf *pf, struct ixl_vf *vf, void *msg,
    uint16_t msg_size)
{
	struct virtchnl_queue_select *queue;

	if (msg_size != sizeof(*queue)) {
		i40e_send_vf_nack(pf, vf, VIRTCHNL_OP_GET_STATS,
		    I40E_ERR_PARAM);
		return;
	}

	queue = msg;
	if (queue->vsi_id != vf->vsi.vsi_num) {
		i40e_send_vf_nack(pf, vf, VIRTCHNL_OP_GET_STATS,
		    I40E_ERR_PARAM);
		return;
	}

	ixl_update_eth_stats(&vf->vsi);

	ixl_send_vf_msg(pf, vf, VIRTCHNL_OP_GET_STATS,
	    I40E_SUCCESS, &vf->vsi.eth_stats, sizeof(vf->vsi.eth_stats));
}