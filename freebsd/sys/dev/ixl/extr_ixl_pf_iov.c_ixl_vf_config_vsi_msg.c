#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct virtchnl_vsi_queue_config_info {int num_queue_pairs; int vsi_id; struct virtchnl_queue_pair_info* qpair; } ;
struct TYPE_6__ {int vsi_id; scalar_t__ queue_id; } ;
struct TYPE_5__ {int vsi_id; scalar_t__ queue_id; } ;
struct virtchnl_queue_pair_info {TYPE_3__ rxq; TYPE_2__ txq; } ;
struct TYPE_4__ {int num_tx_queues; int vsi_num; } ;
struct ixl_vf {TYPE_1__ vsi; int /*<<< orphan*/  vf_num; } ;
struct ixl_pf {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  I40E_ERR_PARAM ; 
 int /*<<< orphan*/  VIRTCHNL_OP_CONFIG_VSI_QUEUES ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  i40e_send_vf_nack (struct ixl_pf*,struct ixl_vf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixl_send_vf_ack (struct ixl_pf*,struct ixl_vf*,int /*<<< orphan*/ ) ; 
 scalar_t__ ixl_vf_config_rx_queue (struct ixl_pf*,struct ixl_vf*,TYPE_3__*) ; 
 scalar_t__ ixl_vf_config_tx_queue (struct ixl_pf*,struct ixl_vf*,TYPE_2__*) ; 

__attribute__((used)) static void
ixl_vf_config_vsi_msg(struct ixl_pf *pf, struct ixl_vf *vf, void *msg,
    uint16_t msg_size)
{
	struct virtchnl_vsi_queue_config_info *info;
	struct virtchnl_queue_pair_info *pair;
	uint16_t expected_msg_size;
	int i;

	if (msg_size < sizeof(*info)) {
		i40e_send_vf_nack(pf, vf, VIRTCHNL_OP_CONFIG_VSI_QUEUES,
		    I40E_ERR_PARAM);
		return;
	}

	info = msg;
	if (info->num_queue_pairs == 0 || info->num_queue_pairs > vf->vsi.num_tx_queues) {
		device_printf(pf->dev, "VF %d: invalid # of qpairs (msg has %d, VSI has %d)\n",
		    vf->vf_num, info->num_queue_pairs, vf->vsi.num_tx_queues);
		i40e_send_vf_nack(pf, vf, VIRTCHNL_OP_CONFIG_VSI_QUEUES,
		    I40E_ERR_PARAM);
		return;
	}

	expected_msg_size = sizeof(*info) + info->num_queue_pairs * sizeof(*pair);
	if (msg_size != expected_msg_size) {
		device_printf(pf->dev, "VF %d: size of recvd message (%d) does not match expected size (%d)\n",
		    vf->vf_num, msg_size, expected_msg_size);
		i40e_send_vf_nack(pf, vf, VIRTCHNL_OP_CONFIG_VSI_QUEUES,
		    I40E_ERR_PARAM);
		return;
	}

	if (info->vsi_id != vf->vsi.vsi_num) {
		device_printf(pf->dev, "VF %d: VSI id in recvd message (%d) does not match expected id (%d)\n",
		    vf->vf_num, info->vsi_id, vf->vsi.vsi_num);
		i40e_send_vf_nack(pf, vf, VIRTCHNL_OP_CONFIG_VSI_QUEUES,
		    I40E_ERR_PARAM);
		return;
	}

	for (i = 0; i < info->num_queue_pairs; i++) {
		pair = &info->qpair[i];

		if (pair->txq.vsi_id != vf->vsi.vsi_num ||
		    pair->rxq.vsi_id != vf->vsi.vsi_num ||
		    pair->txq.queue_id != pair->rxq.queue_id ||
		    pair->txq.queue_id >= vf->vsi.num_tx_queues) {

			i40e_send_vf_nack(pf, vf,
			    VIRTCHNL_OP_CONFIG_VSI_QUEUES, I40E_ERR_PARAM);
			return;
		}

		if (ixl_vf_config_tx_queue(pf, vf, &pair->txq) != 0) {
			i40e_send_vf_nack(pf, vf,
			    VIRTCHNL_OP_CONFIG_VSI_QUEUES, I40E_ERR_PARAM);
			return;
		}

		if (ixl_vf_config_rx_queue(pf, vf, &pair->rxq) != 0) {
			i40e_send_vf_nack(pf, vf,
			    VIRTCHNL_OP_CONFIG_VSI_QUEUES, I40E_ERR_PARAM);
			return;
		}
	}

	ixl_send_vf_ack(pf, vf, VIRTCHNL_OP_CONFIG_VSI_QUEUES);
}