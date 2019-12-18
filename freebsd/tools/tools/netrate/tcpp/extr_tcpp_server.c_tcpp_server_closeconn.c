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
struct connection {int /*<<< orphan*/  conn_fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  bzero (struct connection*,int) ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct connection*) ; 

__attribute__((used)) static void
tcpp_server_closeconn(struct connection *conn)
{

	/*
	 * Kqueue cleans up after itself once we close the socket, and since
	 * we are processing only one kevent at a time, we don't need to
	 * worry about watching out for future kevents referring to it.
	 *
	 * ... right?
	 */
	close(conn->conn_fd);
	bzero(conn, sizeof(*conn));
	free(conn);
}