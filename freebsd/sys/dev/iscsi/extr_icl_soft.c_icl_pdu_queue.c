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
struct icl_pdu {struct icl_conn* ip_conn; } ;
struct icl_conn {int /*<<< orphan*/  ic_send_cv; int /*<<< orphan*/  ic_to_send; int /*<<< orphan*/ * ic_socket; scalar_t__ ic_disconnecting; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICL_CONN_LOCK_ASSERT (struct icl_conn*) ; 
 int /*<<< orphan*/  ICL_DEBUG (char*) ; 
 int /*<<< orphan*/  STAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct icl_pdu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cv_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  icl_soft_conn_pdu_free (struct icl_conn*,struct icl_pdu*) ; 
 int /*<<< orphan*/  ip_next ; 

__attribute__((used)) static void
icl_pdu_queue(struct icl_pdu *ip)
{
	struct icl_conn *ic;

	ic = ip->ip_conn;

	ICL_CONN_LOCK_ASSERT(ic);

	if (ic->ic_disconnecting || ic->ic_socket == NULL) {
		ICL_DEBUG("icl_pdu_queue on closed connection");
		icl_soft_conn_pdu_free(ic, ip);
		return;
	}

	if (!STAILQ_EMPTY(&ic->ic_to_send)) {
		STAILQ_INSERT_TAIL(&ic->ic_to_send, ip, ip_next);
		/*
		 * If the queue is not empty, someone else had already
		 * signaled the send thread; no need to do that again,
		 * just return.
		 */
		return;
	}

	STAILQ_INSERT_TAIL(&ic->ic_to_send, ip, ip_next);
	cv_signal(&ic->ic_send_cv);
}