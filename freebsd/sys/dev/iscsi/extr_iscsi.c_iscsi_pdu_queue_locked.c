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
struct iscsi_session {int /*<<< orphan*/  is_postponed; int /*<<< orphan*/  is_sim; } ;
struct icl_pdu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISCSI_SESSION_LOCK_ASSERT (struct iscsi_session*) ; 
 struct iscsi_session* PDU_SESSION (struct icl_pdu*) ; 
 scalar_t__ STAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct icl_pdu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  icl_pdu_queue (struct icl_pdu*) ; 
 int /*<<< orphan*/  ip_next ; 
 int iscsi_pdu_prepare (struct icl_pdu*) ; 
 int /*<<< orphan*/  iscsi_session_send_postponed (struct iscsi_session*) ; 
 int /*<<< orphan*/  xpt_freeze_simq (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
iscsi_pdu_queue_locked(struct icl_pdu *request)
{
	struct iscsi_session *is;
	bool postpone;

	is = PDU_SESSION(request);
	ISCSI_SESSION_LOCK_ASSERT(is);
	iscsi_session_send_postponed(is);
	postpone = iscsi_pdu_prepare(request);
	if (postpone) {
		if (STAILQ_EMPTY(&is->is_postponed))
			xpt_freeze_simq(is->is_sim, 1);
		STAILQ_INSERT_TAIL(&is->is_postponed, request, ip_next);
		return;
	}
	icl_pdu_queue(request);
}