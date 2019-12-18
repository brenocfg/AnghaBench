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
typedef  int /*<<< orphan*/  tv ;
struct timeval {int tv_sec; scalar_t__ tv_usec; } ;
struct proto_conn {scalar_t__ pc_magic; int /*<<< orphan*/ * pc_proto; } ;

/* Variables and functions */
 int /*<<< orphan*/  PJDLOG_ASSERT (int) ; 
 scalar_t__ PROTO_CONN_MAGIC ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_RCVTIMEO ; 
 int /*<<< orphan*/  SO_SNDTIMEO ; 
 int proto_descriptor (struct proto_conn const*) ; 
 scalar_t__ setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct timeval*,int) ; 

int
proto_timeout(const struct proto_conn *conn, int timeout)
{
	struct timeval tv;
	int fd;

	PJDLOG_ASSERT(conn != NULL);
	PJDLOG_ASSERT(conn->pc_magic == PROTO_CONN_MAGIC);
	PJDLOG_ASSERT(conn->pc_proto != NULL);

	fd = proto_descriptor(conn);
	if (fd < 0)
		return (-1);

	tv.tv_sec = timeout;
	tv.tv_usec = 0;
	if (setsockopt(fd, SOL_SOCKET, SO_SNDTIMEO, &tv, sizeof(tv)) < 0)
		return (-1);
	if (setsockopt(fd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv)) < 0)
		return (-1);

	return (0);
}