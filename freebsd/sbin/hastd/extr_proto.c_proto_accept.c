#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct proto_conn {scalar_t__ pc_magic; scalar_t__ pc_side; int /*<<< orphan*/  pc_ctx; TYPE_1__* pc_proto; } ;
struct TYPE_2__ {int (* prt_accept ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  PJDLOG_ASSERT (int) ; 
 scalar_t__ PROTO_CONN_MAGIC ; 
 scalar_t__ PROTO_SIDE_SERVER_LISTEN ; 
 int /*<<< orphan*/  PROTO_SIDE_SERVER_WORK ; 
 int errno ; 
 struct proto_conn* proto_alloc (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proto_free (struct proto_conn*) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
proto_accept(struct proto_conn *conn, struct proto_conn **newconnp)
{
	struct proto_conn *newconn;
	int ret;

	PJDLOG_ASSERT(conn != NULL);
	PJDLOG_ASSERT(conn->pc_magic == PROTO_CONN_MAGIC);
	PJDLOG_ASSERT(conn->pc_side == PROTO_SIDE_SERVER_LISTEN);
	PJDLOG_ASSERT(conn->pc_proto != NULL);
	PJDLOG_ASSERT(conn->pc_proto->prt_accept != NULL);

	newconn = proto_alloc(conn->pc_proto, PROTO_SIDE_SERVER_WORK);
	if (newconn == NULL)
		return (-1);

	ret = conn->pc_proto->prt_accept(conn->pc_ctx, &newconn->pc_ctx);
	if (ret != 0) {
		proto_free(newconn);
		errno = ret;
		return (-1);
	}

	*newconnp = newconn;

	return (0);
}