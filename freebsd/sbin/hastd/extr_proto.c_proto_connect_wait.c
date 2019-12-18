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
struct TYPE_2__ {int (* prt_connect_wait ) (int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  PJDLOG_ASSERT (int) ; 
 scalar_t__ PROTO_CONN_MAGIC ; 
 scalar_t__ PROTO_SIDE_CLIENT ; 
 int errno ; 
 int stub1 (int /*<<< orphan*/ ,int) ; 

int
proto_connect_wait(struct proto_conn *conn, int timeout)
{
	int ret;

	PJDLOG_ASSERT(conn != NULL);
	PJDLOG_ASSERT(conn->pc_magic == PROTO_CONN_MAGIC);
	PJDLOG_ASSERT(conn->pc_side == PROTO_SIDE_CLIENT);
	PJDLOG_ASSERT(conn->pc_proto != NULL);
	PJDLOG_ASSERT(conn->pc_proto->prt_connect_wait != NULL);
	PJDLOG_ASSERT(timeout >= 0);

	ret = conn->pc_proto->prt_connect_wait(conn->pc_ctx, timeout);
	if (ret != 0) {
		errno = ret;
		return (-1);
	}

	return (0);
}