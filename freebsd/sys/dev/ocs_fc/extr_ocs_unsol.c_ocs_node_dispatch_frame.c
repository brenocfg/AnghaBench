#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_6__ ;
typedef  struct TYPE_29__   TYPE_5__ ;
typedef  struct TYPE_28__   TYPE_4__ ;
typedef  struct TYPE_27__   TYPE_3__ ;
typedef  struct TYPE_26__   TYPE_2__ ;
typedef  struct TYPE_25__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_27__ {scalar_t__ fc_id; } ;
struct TYPE_28__ {int /*<<< orphan*/  fcp_enabled; TYPE_3__ rnode; } ;
typedef  TYPE_4__ ocs_node_t ;
struct TYPE_29__ {TYPE_2__* header; } ;
typedef  TYPE_5__ ocs_hw_sequence_t ;
typedef  int int32_t ;
struct TYPE_30__ {int r_ctl; int /*<<< orphan*/  info; int /*<<< orphan*/  type; int /*<<< orphan*/  f_ctl; int /*<<< orphan*/  s_id; } ;
typedef  TYPE_6__ fc_header_t ;
struct TYPE_25__ {TYPE_6__* virt; } ;
struct TYPE_26__ {TYPE_1__ dma; } ;

/* Variables and functions */
 int FC_FCTL_END_SEQUENCE ; 
 int FC_FCTL_SEQUENCE_INITIATIVE ; 
#define  FC_RCTL_BLS 132 
#define  FC_RCTL_ELS 131 
#define  FC_RCTL_FC4_DATA 130 
 int /*<<< orphan*/  FC_RCTL_INFO_SOL_DATA ; 
 int /*<<< orphan*/  FC_RCTL_INFO_UNSOL_CMD ; 
#define  FC_TYPE_FCP 129 
#define  FC_TYPE_GS 128 
 int fc_be24toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  node_printf (TYPE_4__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_assert (int,int) ; 
 int ocs_dispatch_fcp_cmd (TYPE_4__*,TYPE_5__*) ; 
 int ocs_dispatch_fcp_cmd_auto_xfer_rdy (TYPE_4__*,TYPE_5__*) ; 
 int ocs_dispatch_fcp_data (TYPE_4__*,TYPE_5__*) ; 
 int /*<<< orphan*/  ocs_htobe32 (scalar_t__) ; 
 int ocs_node_recv_abts_frame (TYPE_4__*,TYPE_5__*) ; 
 int ocs_node_recv_bls_no_sit (TYPE_4__*,TYPE_5__*) ; 
 int ocs_node_recv_ct_frame (TYPE_4__*,TYPE_5__*) ; 
 int ocs_node_recv_els_frame (TYPE_4__*,TYPE_5__*) ; 
 int ocs_node_recv_fcp_cmd (TYPE_4__*,TYPE_5__*) ; 

__attribute__((used)) static int32_t
ocs_node_dispatch_frame(void *arg, ocs_hw_sequence_t *seq)
{

	fc_header_t *hdr = seq->header->dma.virt;
	uint32_t port_id;
	ocs_node_t *node = (ocs_node_t *)arg;
	int32_t rc = -1;
	int32_t sit_set = 0;

	port_id = fc_be24toh(hdr->s_id);
	ocs_assert(port_id == node->rnode.fc_id, -1);

	if (fc_be24toh(hdr->f_ctl) & FC_FCTL_END_SEQUENCE) {
		/*if SIT is set */
		if (fc_be24toh(hdr->f_ctl) & FC_FCTL_SEQUENCE_INITIATIVE) {
			sit_set = 1;
		}
		switch (hdr->r_ctl) {
		case FC_RCTL_ELS:
			if (sit_set) {
				rc = ocs_node_recv_els_frame(node, seq);
			}
			break;

		case FC_RCTL_BLS:
			if (sit_set) {
				rc = ocs_node_recv_abts_frame(node, seq);
			}else {
				rc = ocs_node_recv_bls_no_sit(node, seq);
			}
			break;

		case FC_RCTL_FC4_DATA:
			switch(hdr->type) {
			case FC_TYPE_FCP:
				if (hdr->info == FC_RCTL_INFO_UNSOL_CMD) {
					if (node->fcp_enabled) {
						if (sit_set) {
							rc = ocs_dispatch_fcp_cmd(node, seq);
						}else {
							/* send the auto xfer ready command */
							rc = ocs_dispatch_fcp_cmd_auto_xfer_rdy(node, seq);
						}
					} else {
						rc = ocs_node_recv_fcp_cmd(node, seq);
					}
				} else if (hdr->info == FC_RCTL_INFO_SOL_DATA) {
					if (sit_set) {
						rc = ocs_dispatch_fcp_data(node, seq);
					}
				}
				break;
			case FC_TYPE_GS:
				if (sit_set) {
					rc = ocs_node_recv_ct_frame(node, seq);
				}
				break;
			default:
				break;
			}
			break;
		}
	} else {
		node_printf(node, "Dropping frame hdr = %08x %08x %08x %08x %08x %08x\n",
			    ocs_htobe32(((uint32_t *)hdr)[0]),
			    ocs_htobe32(((uint32_t *)hdr)[1]),
			    ocs_htobe32(((uint32_t *)hdr)[2]),
			    ocs_htobe32(((uint32_t *)hdr)[3]),
			    ocs_htobe32(((uint32_t *)hdr)[4]),
			    ocs_htobe32(((uint32_t *)hdr)[5]));
	}
	return rc;
}