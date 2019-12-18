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
struct ib_ucm_req_event_resp {int /*<<< orphan*/  alternate_path; int /*<<< orphan*/  primary_path; int /*<<< orphan*/  port; int /*<<< orphan*/  srq; int /*<<< orphan*/  rnr_retry_count; int /*<<< orphan*/  retry_count; int /*<<< orphan*/  remote_cm_response_timeout; int /*<<< orphan*/  flow_control; int /*<<< orphan*/  local_cm_response_timeout; int /*<<< orphan*/  initiator_depth; int /*<<< orphan*/  responder_resources; int /*<<< orphan*/  starting_psn; int /*<<< orphan*/  qp_type; int /*<<< orphan*/  remote_qpn; int /*<<< orphan*/  remote_qkey; int /*<<< orphan*/  remote_ca_guid; } ;
struct ib_cm_req_event_param {scalar_t__ alternate_path; scalar_t__ primary_path; int /*<<< orphan*/  port; int /*<<< orphan*/  srq; int /*<<< orphan*/  rnr_retry_count; int /*<<< orphan*/  retry_count; int /*<<< orphan*/  remote_cm_response_timeout; int /*<<< orphan*/  flow_control; int /*<<< orphan*/  local_cm_response_timeout; int /*<<< orphan*/  initiator_depth; int /*<<< orphan*/  responder_resources; int /*<<< orphan*/  starting_psn; int /*<<< orphan*/  qp_type; int /*<<< orphan*/  remote_qpn; int /*<<< orphan*/  remote_qkey; int /*<<< orphan*/  remote_ca_guid; } ;

/* Variables and functions */
 int /*<<< orphan*/  ibv_copy_path_rec_from_kern (scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cm_event_req_get(struct ib_cm_req_event_param *ureq,
			     struct ib_ucm_req_event_resp *kreq)
{
	ureq->remote_ca_guid             = kreq->remote_ca_guid;
	ureq->remote_qkey                = kreq->remote_qkey;
	ureq->remote_qpn                 = kreq->remote_qpn;
	ureq->qp_type                    = kreq->qp_type;
	ureq->starting_psn               = kreq->starting_psn;
	ureq->responder_resources        = kreq->responder_resources;
	ureq->initiator_depth            = kreq->initiator_depth;
	ureq->local_cm_response_timeout  = kreq->local_cm_response_timeout;
	ureq->flow_control               = kreq->flow_control;
	ureq->remote_cm_response_timeout = kreq->remote_cm_response_timeout;
	ureq->retry_count                = kreq->retry_count;
	ureq->rnr_retry_count            = kreq->rnr_retry_count;
	ureq->srq                        = kreq->srq;
	ureq->port			 = kreq->port;

	ibv_copy_path_rec_from_kern(ureq->primary_path, &kreq->primary_path);
	if (ureq->alternate_path)
		ibv_copy_path_rec_from_kern(ureq->alternate_path,
					    &kreq->alternate_path);
}