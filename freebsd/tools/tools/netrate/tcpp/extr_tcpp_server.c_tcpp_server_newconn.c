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
struct kevent {int dummy; } ;
struct connection {int conn_fd; int /*<<< orphan*/  conn_magic; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONNECTION_MAGIC ; 
 int /*<<< orphan*/  EVFILT_READ ; 
 int /*<<< orphan*/  EV_ADD ; 
 int /*<<< orphan*/  EV_SET (struct kevent*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct connection*) ; 
 int /*<<< orphan*/  F_SETFL ; 
 int /*<<< orphan*/  O_NONBLOCK ; 
 int accept (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bzero (struct connection*,int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 scalar_t__ fcntl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ kevent (int /*<<< orphan*/ ,struct kevent*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kq ; 
 struct connection* malloc (int) ; 
 int /*<<< orphan*/  warn (char*) ; 

__attribute__((used)) static struct connection *
tcpp_server_newconn(int listen_fd)
{
	struct connection *conn;
	struct kevent kev;
	int fd;

	fd = accept(listen_fd, NULL, NULL);
	if (fd < 0) {
		warn("accept");
		return (NULL);
	}

	if (fcntl(fd, F_SETFL, O_NONBLOCK) < 0)
		err(-1, "fcntl");

	conn = malloc(sizeof(*conn));
	if (conn == NULL)
		return (NULL);
	bzero(conn, sizeof(*conn));
	conn->conn_magic = CONNECTION_MAGIC;
	conn->conn_fd = fd;

	/*
	 * Register to read on the socket, and set our conn pointer as the
	 * udata so we can find it quickly in the future.
	 */
	EV_SET(&kev, fd, EVFILT_READ, EV_ADD, 0, 0, conn);
	if (kevent(kq, &kev, 1, NULL, 0, NULL) < 0)
		err(-1, "kevent");

	return (conn);
}