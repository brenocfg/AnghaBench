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
 int /*<<< orphan*/  finished ; 
 int /*<<< orphan*/  free (struct connection*) ; 

__attribute__((used)) static void
tcpp_client_closeconn(struct connection *conn)
{

	close(conn->conn_fd);
	bzero(conn, sizeof(*conn));
	free(conn);
	finished++;
}