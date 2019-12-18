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
typedef  int /*<<< orphan*/  sun ;
struct sockaddr_un {int sun_len; int /*<<< orphan*/  sun_path; int /*<<< orphan*/  sun_family; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  socket_path ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNIX ; 
 scalar_t__ EADDRINUSE ; 
 scalar_t__ EINVAL ; 
 int PATH_MAX ; 
 int /*<<< orphan*/  PF_UNIX ; 
 char* SOCK_NAME_ONE ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 scalar_t__ bind (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  bzero (struct sockaddr_un*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  push_path (char*) ; 
 int snprintf (char*,int,char*,char const*,...) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlink (char*) ; 
 int /*<<< orphan*/  warn (char*) ; 
 int /*<<< orphan*/  warnx (char*) ; 

__attribute__((used)) static int
bind_test(const char *directory_path)
{
	char socket_path[PATH_MAX];
	struct sockaddr_un sun;
	int sock1, sock2;

	sock1 = socket(PF_UNIX, SOCK_STREAM, 0);
	if (sock1 < 0) {
		warn("bind_test: socket(PF_UNIX, SOCK_STREAM, 0)");
		return (-1);
	}

	if (snprintf(socket_path, sizeof(socket_path), "%s/%s",
	    directory_path, SOCK_NAME_ONE) >= PATH_MAX) {
		warn("bind_test: snprintf(socket_path)");
		close(sock1);
		return (-1);
	}

	bzero(&sun, sizeof(sun));
	sun.sun_len = sizeof(sun);
	sun.sun_family = AF_UNIX;
	if (snprintf(sun.sun_path, sizeof(sun.sun_path), "%s", socket_path)
	    >= (int)sizeof(sun.sun_path)) {
		warn("bind_test: snprintf(sun.sun_path)");
		close(sock1);
		return (-1);
	}

	if (bind(sock1, (struct sockaddr *)&sun, sizeof(sun)) < 0) {
		warn("bind_test: bind(sun) #1");
		close(sock1);
		return (-1);
	}

	push_path(socket_path);

	/*
	 * Once a STREAM UNIX domain socket has been bound, it can't be
	 * rebound.  Expected error is EINVAL.
	 */
	if (bind(sock1, (struct sockaddr *)&sun, sizeof(sun)) == 0) {
		warnx("bind_test: bind(sun) #2 succeeded");
		close(sock1);
		return (-1);
	}
	if (errno != EINVAL) {
		warn("bind_test: bind(sun) #2");
		close(sock1);
		return (-1);
	}

	sock2 = socket(PF_UNIX, SOCK_STREAM, 0);
	if (sock2 < 0) {
		warn("bind_test: socket(PF_UNIX, SOCK_STREAM, 0)");
		close(sock1);
		return (-1);
	}

	/*
	 * Since a socket is already bound to the pathname, it can't be bound
	 * to a second socket.  Expected error is EADDRINUSE.
	 */
	if (bind(sock2, (struct sockaddr *)&sun, sizeof(sun)) == 0) {
		warnx("bind_test: bind(sun) #3 succeeded");
		close(sock1);
		close(sock2);
		return (-1);
	}
	if (errno != EADDRINUSE) {
		warn("bind_test: bind(sun) #2");
		close(sock1);
		close(sock2);
		return (-1);
	}

	close(sock1);

	/*
	 * The socket bound to the pathname has been closed, but the pathname
	 * can't be reused without first being unlinked.  Expected error is
	 * EADDRINUSE.
	 */
	if (bind(sock2, (struct sockaddr *)&sun, sizeof(sun)) == 0) {
		warnx("bind_test: bind(sun) #4 succeeded");
		close(sock2);
		return (-1);
	}
	if (errno != EADDRINUSE) {
		warn("bind_test: bind(sun) #4");
		close(sock2);
		return (-1);
	}

	unlink(socket_path);

	/*
	 * The pathname is now free, so the socket should be able to bind to
	 * it.
	 */
	if (bind(sock2, (struct sockaddr *)&sun, sizeof(sun)) < 0) {
		warn("bind_test: bind(sun) #5");
		close(sock2);
		return (-1);
	}

	close(sock2);
	return (0);
}