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
struct proto_conn {scalar_t__ pc_magic; int /*<<< orphan*/  pc_ctx; TYPE_1__* pc_proto; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* prt_remote_address ) (int /*<<< orphan*/ ,char*,size_t) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  PJDLOG_ASSERT (int) ; 
 scalar_t__ PROTO_CONN_MAGIC ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*,size_t) ; 

void
proto_remote_address(const struct proto_conn *conn, char *addr, size_t size)
{

	PJDLOG_ASSERT(conn != NULL);
	PJDLOG_ASSERT(conn->pc_magic == PROTO_CONN_MAGIC);
	PJDLOG_ASSERT(conn->pc_proto != NULL);
	PJDLOG_ASSERT(conn->pc_proto->prt_remote_address != NULL);

	conn->pc_proto->prt_remote_address(conn->pc_ctx, addr, size);
}