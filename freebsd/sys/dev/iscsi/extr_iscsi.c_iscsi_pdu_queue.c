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
struct iscsi_session {int dummy; } ;
struct icl_pdu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISCSI_SESSION_LOCK (struct iscsi_session*) ; 
 int /*<<< orphan*/  ISCSI_SESSION_UNLOCK (struct iscsi_session*) ; 
 struct iscsi_session* PDU_SESSION (struct icl_pdu*) ; 
 int /*<<< orphan*/  iscsi_pdu_queue_locked (struct icl_pdu*) ; 

__attribute__((used)) static void
iscsi_pdu_queue(struct icl_pdu *request)
{
	struct iscsi_session *is;

	is = PDU_SESSION(request);
	ISCSI_SESSION_LOCK(is);
	iscsi_pdu_queue_locked(request);
	ISCSI_SESSION_UNLOCK(is);
}