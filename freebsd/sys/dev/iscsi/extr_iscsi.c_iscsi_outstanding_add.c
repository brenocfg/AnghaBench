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
union ccb {int /*<<< orphan*/  csio; } ;
typedef  int /*<<< orphan*/  uint32_t ;
struct iscsi_session {int /*<<< orphan*/  is_outstanding; int /*<<< orphan*/  is_conn; } ;
struct iscsi_outstanding {union ccb* io_ccb; int /*<<< orphan*/  io_initiator_task_tag; int /*<<< orphan*/  io_icl_prv; } ;
struct icl_pdu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISCSI_SESSION_LOCK_ASSERT (struct iscsi_session*) ; 
 int /*<<< orphan*/  ISCSI_SESSION_WARN (struct iscsi_session*,char*,int) ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct iscsi_outstanding*,int /*<<< orphan*/ ) ; 
 int icl_conn_task_setup (int /*<<< orphan*/ ,struct icl_pdu*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  io_next ; 
 int /*<<< orphan*/ * iscsi_outstanding_find (struct iscsi_session*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iscsi_outstanding_zone ; 
 struct iscsi_outstanding* uma_zalloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uma_zfree (int /*<<< orphan*/ ,struct iscsi_outstanding*) ; 

__attribute__((used)) static struct iscsi_outstanding *
iscsi_outstanding_add(struct iscsi_session *is, struct icl_pdu *request,
    union ccb *ccb, uint32_t *initiator_task_tagp)
{
	struct iscsi_outstanding *io;
	int error;

	ISCSI_SESSION_LOCK_ASSERT(is);

	io = uma_zalloc(iscsi_outstanding_zone, M_NOWAIT | M_ZERO);
	if (io == NULL) {
		ISCSI_SESSION_WARN(is, "failed to allocate %zd bytes",
		    sizeof(*io));
		return (NULL);
	}

	error = icl_conn_task_setup(is->is_conn, request, &ccb->csio,
	    initiator_task_tagp, &io->io_icl_prv);
	if (error != 0) {
		ISCSI_SESSION_WARN(is,
		    "icl_conn_task_setup() failed with error %d", error);
		uma_zfree(iscsi_outstanding_zone, io);
		return (NULL);
	}

	KASSERT(iscsi_outstanding_find(is, *initiator_task_tagp) == NULL,
	    ("initiator_task_tag 0x%x already added", *initiator_task_tagp));

	io->io_initiator_task_tag = *initiator_task_tagp;
	io->io_ccb = ccb;
	TAILQ_INSERT_TAIL(&is->is_outstanding, io, io_next);
	return (io);
}