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
struct TYPE_2__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {TYPE_1__ sin_addr; } ;
struct sockaddr {int dummy; } ;
struct ggd_connection {int c_sendfd; int c_recvfd; int c_flags; int /*<<< orphan*/ * c_path; int /*<<< orphan*/  c_birthtime; scalar_t__ c_sectorsize; scalar_t__ c_mediasize; int /*<<< orphan*/  c_srcip; int /*<<< orphan*/  c_token; } ;
struct g_gate_cinit {int gc_flags; int /*<<< orphan*/  gc_token; int /*<<< orphan*/  gc_path; } ;
typedef  int /*<<< orphan*/  in_addr_t ;

/* Variables and functions */
 int GGATE_FLAG_SEND ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,struct ggd_connection*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  c_next ; 
 int /*<<< orphan*/  connection_cleanups () ; 
 int /*<<< orphan*/  connections ; 
 int /*<<< orphan*/  free (struct ggd_connection*) ; 
 int /*<<< orphan*/  g_gate_log (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip2str (int /*<<< orphan*/ ) ; 
 struct ggd_connection* malloc (int) ; 
 int /*<<< orphan*/ * strdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct ggd_connection *
connection_new(struct g_gate_cinit *cinit, struct sockaddr *s, int sfd)
{
	struct ggd_connection *conn;
	in_addr_t ip;

	/*
	 * First, look for old connections.
	 * We probably should do it every X seconds, but what for?
	 * It is only dangerous if an attacker wants to overload connections
	 * queue, so here is a good place to do the cleanups.
	 */
	connection_cleanups();

	conn = malloc(sizeof(*conn));
	if (conn == NULL)
		return (NULL);
	conn->c_path = strdup(cinit->gc_path);
	if (conn->c_path == NULL) {
		free(conn);
		return (NULL);
	}
	conn->c_token = cinit->gc_token;
	ip = htonl(((struct sockaddr_in *)(void *)s)->sin_addr.s_addr);
	conn->c_srcip = ip;
	conn->c_sendfd = conn->c_recvfd = -1;
	if ((cinit->gc_flags & GGATE_FLAG_SEND) != 0)
		conn->c_sendfd = sfd;
	else
		conn->c_recvfd = sfd;
	conn->c_mediasize = 0;
	conn->c_sectorsize = 0;
	time(&conn->c_birthtime);
	conn->c_flags = cinit->gc_flags;
	LIST_INSERT_HEAD(&connections, conn, c_next);
	g_gate_log(LOG_DEBUG, "Connection created [%s, %s].", ip2str(ip),
	    conn->c_path);
	return (conn);
}