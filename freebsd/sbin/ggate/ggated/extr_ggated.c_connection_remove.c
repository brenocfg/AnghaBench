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
struct ggd_connection {int c_sendfd; int c_recvfd; struct ggd_connection* c_path; int /*<<< orphan*/  c_srcip; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_REMOVE (struct ggd_connection*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  c_next ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  free (struct ggd_connection*) ; 
 int /*<<< orphan*/  g_gate_log (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,struct ggd_connection*) ; 
 int /*<<< orphan*/  ip2str (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
connection_remove(struct ggd_connection *conn)
{

	LIST_REMOVE(conn, c_next);
	g_gate_log(LOG_DEBUG, "Connection removed [%s %s].",
	    ip2str(conn->c_srcip), conn->c_path);
	if (conn->c_sendfd != -1)
		close(conn->c_sendfd);
	if (conn->c_recvfd != -1)
		close(conn->c_recvfd);
	free(conn->c_path);
	free(conn);
}