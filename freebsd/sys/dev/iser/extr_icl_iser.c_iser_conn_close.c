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
struct iser_conn {scalar_t__ state; int /*<<< orphan*/  state_mutex; int /*<<< orphan*/  up_cv; } ;
struct icl_conn {int dummy; } ;

/* Variables and functions */
 scalar_t__ ISER_CONN_PENDING ; 
 int /*<<< orphan*/  ISER_INFO (char*,struct iser_conn*) ; 
 int /*<<< orphan*/  cv_signal (int /*<<< orphan*/ *) ; 
 struct iser_conn* icl_to_iser_conn (struct icl_conn*) ; 
 int /*<<< orphan*/  iser_conn_terminate (struct iser_conn*) ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 

void
iser_conn_close(struct icl_conn *ic)
{
	struct iser_conn *iser_conn = icl_to_iser_conn(ic);

	ISER_INFO("closing conn %p", iser_conn);

	sx_xlock(&iser_conn->state_mutex);
	/*
	 * In case iser connection is waiting on conditional variable
	 * (state PENDING) and we try to close it before connection establishment,
	 * we need to signal it to continue releasing connection properly.
	 */
	if (!iser_conn_terminate(iser_conn) && iser_conn->state == ISER_CONN_PENDING)
		cv_signal(&iser_conn->up_cv);
	sx_xunlock(&iser_conn->state_mutex);

}