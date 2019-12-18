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
struct iscsi_session {int /*<<< orphan*/  is_sim; int /*<<< orphan*/  is_postponed; } ;
struct icl_pdu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISCSI_SESSION_LOCK_ASSERT (struct iscsi_session*) ; 
 scalar_t__ STAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 struct icl_pdu* STAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_REMOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  icl_pdu_queue (struct icl_pdu*) ; 
 int /*<<< orphan*/  ip_next ; 
 int iscsi_pdu_prepare (struct icl_pdu*) ; 
 int /*<<< orphan*/  xpt_release_simq (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
iscsi_session_send_postponed(struct iscsi_session *is)
{
	struct icl_pdu *request;
	bool postpone;

	ISCSI_SESSION_LOCK_ASSERT(is);

	if (STAILQ_EMPTY(&is->is_postponed))
		return;
	while ((request = STAILQ_FIRST(&is->is_postponed)) != NULL) {
		postpone = iscsi_pdu_prepare(request);
		if (postpone)
			return;
		STAILQ_REMOVE_HEAD(&is->is_postponed, ip_next);
		icl_pdu_queue(request);
	}
	xpt_release_simq(is->is_sim, 1);
}