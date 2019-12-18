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
struct TYPE_2__ {int (* prt_send ) (int /*<<< orphan*/ ,unsigned char const*,scalar_t__,int) ;char* prt_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  PJDLOG_ASSERT (int) ; 
 scalar_t__ PROTO_CONN_MAGIC ; 
 int errno ; 
 int /*<<< orphan*/  proto_close (struct proto_conn*) ; 
 int proto_descriptor (struct proto_conn*) ; 
 scalar_t__ strlen (char const*) ; 
 int stub1 (int /*<<< orphan*/ ,unsigned char const*,scalar_t__,int) ; 

int
proto_connection_send(const struct proto_conn *conn, struct proto_conn *mconn)
{
	const char *protoname;
	int error, fd;

	PJDLOG_ASSERT(conn != NULL);
	PJDLOG_ASSERT(conn->pc_magic == PROTO_CONN_MAGIC);
	PJDLOG_ASSERT(conn->pc_proto != NULL);
	PJDLOG_ASSERT(conn->pc_proto->prt_send != NULL);
	PJDLOG_ASSERT(mconn != NULL);
	PJDLOG_ASSERT(mconn->pc_magic == PROTO_CONN_MAGIC);
	PJDLOG_ASSERT(mconn->pc_proto != NULL);
	fd = proto_descriptor(mconn);
	PJDLOG_ASSERT(fd >= 0);
	protoname = mconn->pc_proto->prt_name;
	PJDLOG_ASSERT(protoname != NULL);

	error = conn->pc_proto->prt_send(conn->pc_ctx,
	    (const unsigned char *)protoname, strlen(protoname) + 1, fd);
	proto_close(mconn);
	if (error != 0) {
		errno = error;
		return (-1);
	}
	return (0);
}