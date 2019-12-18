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
typedef  int /*<<< orphan*/  protoname ;
struct TYPE_2__ {int (* prt_recv ) (int /*<<< orphan*/ ,unsigned char*,int,int*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  PJDLOG_ASSERT (int) ; 
 scalar_t__ PROTO_CONN_MAGIC ; 
 int /*<<< orphan*/  bzero (char*,int) ; 
 int errno ; 
 int proto_wrap (char*,int,int,struct proto_conn**) ; 
 int stub1 (int /*<<< orphan*/ ,unsigned char*,int,int*) ; 

int
proto_connection_recv(const struct proto_conn *conn, bool client,
    struct proto_conn **newconnp)
{
	char protoname[128];
	int error, fd;

	PJDLOG_ASSERT(conn != NULL);
	PJDLOG_ASSERT(conn->pc_magic == PROTO_CONN_MAGIC);
	PJDLOG_ASSERT(conn->pc_proto != NULL);
	PJDLOG_ASSERT(conn->pc_proto->prt_recv != NULL);
	PJDLOG_ASSERT(newconnp != NULL);

	bzero(protoname, sizeof(protoname));

	error = conn->pc_proto->prt_recv(conn->pc_ctx,
	    (unsigned char *)protoname, sizeof(protoname) - 1, &fd);
	if (error != 0) {
		errno = error;
		return (-1);
	}

	PJDLOG_ASSERT(fd >= 0);

	return (proto_wrap(protoname, client, fd, newconnp));
}