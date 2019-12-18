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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  ocs_node_t ;
typedef  int /*<<< orphan*/  ocs_hw_sequence_t ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int FC_FCTL_END_SEQUENCE ; 
 int FC_FCTL_EXCHANGE_RESPONDER ; 
 int FC_FCTL_LAST_SEQUENCE ; 
 int FC_FCTL_SEQUENCE_INITIATIVE ; 
 int /*<<< orphan*/  FC_RCTL_FC4_DATA ; 
 int /*<<< orphan*/  FC_RCTL_INFO_CMD_STATUS ; 
 int /*<<< orphan*/  FC_TYPE_FCP ; 
 int /*<<< orphan*/  ocs_sframe_common_send (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int32_t
ocs_sframe_send_fcp_rsp(ocs_node_t *node, ocs_hw_sequence_t *seq, void *rsp, uint32_t rsp_len)
{
	return ocs_sframe_common_send(node, seq,
				      FC_RCTL_FC4_DATA,
				      FC_RCTL_INFO_CMD_STATUS,
				      FC_FCTL_EXCHANGE_RESPONDER |
					      FC_FCTL_LAST_SEQUENCE |
					      FC_FCTL_END_SEQUENCE |
					      FC_FCTL_SEQUENCE_INITIATIVE,
				      FC_TYPE_FCP,
				      rsp, rsp_len);
}