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
struct iscsi_session {int /*<<< orphan*/  is_outstanding; int /*<<< orphan*/  is_conn; } ;
struct iscsi_outstanding {int /*<<< orphan*/  io_icl_prv; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISCSI_SESSION_LOCK_ASSERT (struct iscsi_session*) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct iscsi_outstanding*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  icl_conn_task_done (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  io_next ; 
 int /*<<< orphan*/  iscsi_outstanding_zone ; 
 int /*<<< orphan*/  uma_zfree (int /*<<< orphan*/ ,struct iscsi_outstanding*) ; 

__attribute__((used)) static void
iscsi_outstanding_remove(struct iscsi_session *is, struct iscsi_outstanding *io)
{

	ISCSI_SESSION_LOCK_ASSERT(is);

	icl_conn_task_done(is->is_conn, io->io_icl_prv);
	TAILQ_REMOVE(&is->is_outstanding, io, io_next);
	uma_zfree(iscsi_outstanding_zone, io);
}