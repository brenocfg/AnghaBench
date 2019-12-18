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
struct proto_conn {scalar_t__ pc_magic; scalar_t__ pc_side; int /*<<< orphan*/ * pc_proto; } ;

/* Variables and functions */
 int /*<<< orphan*/  PJDLOG_ASSERT (int) ; 
 scalar_t__ PROTO_CONN_MAGIC ; 
 scalar_t__ PROTO_SIDE_CLIENT ; 
 scalar_t__ PROTO_SIDE_SERVER_LISTEN ; 
 scalar_t__ PROTO_SIDE_SERVER_WORK ; 
 int /*<<< orphan*/  bzero (struct proto_conn*,int) ; 
 int /*<<< orphan*/  free (struct proto_conn*) ; 

__attribute__((used)) static void
proto_free(struct proto_conn *conn)
{

	PJDLOG_ASSERT(conn != NULL);
	PJDLOG_ASSERT(conn->pc_magic == PROTO_CONN_MAGIC);
	PJDLOG_ASSERT(conn->pc_side == PROTO_SIDE_CLIENT ||
	    conn->pc_side == PROTO_SIDE_SERVER_LISTEN ||
	    conn->pc_side == PROTO_SIDE_SERVER_WORK);
	PJDLOG_ASSERT(conn->pc_proto != NULL);

	bzero(conn, sizeof(*conn));
	free(conn);
}