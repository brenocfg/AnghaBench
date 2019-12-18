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
struct icl_pdu {int dummy; } ;
struct cfiscsi_session {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CFISCSI_SESSION_LOCK (struct cfiscsi_session*) ; 
 int /*<<< orphan*/  CFISCSI_SESSION_UNLOCK (struct cfiscsi_session*) ; 
 struct cfiscsi_session* PDU_SESSION (struct icl_pdu*) ; 
 int /*<<< orphan*/  cfiscsi_pdu_prepare (struct icl_pdu*) ; 
 int /*<<< orphan*/  icl_pdu_queue (struct icl_pdu*) ; 

__attribute__((used)) static void
cfiscsi_pdu_queue(struct icl_pdu *response)
{
	struct cfiscsi_session *cs;

	cs = PDU_SESSION(response);

	CFISCSI_SESSION_LOCK(cs);
	cfiscsi_pdu_prepare(response);
	icl_pdu_queue(response);
	CFISCSI_SESSION_UNLOCK(cs);
}