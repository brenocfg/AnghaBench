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
 scalar_t__ ECONNREFUSED ; 
 scalar_t__ ENOENT ; 
 int PATH_MAX ; 
 int /*<<< orphan*/  PF_UNIX ; 
 char* SOCK_NAME_TWO ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 scalar_t__ bind (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  bzero (struct sockaddr_un*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ connect (int,struct sockaddr*,int) ; 
 scalar_t__ errno ; 
 scalar_t__ listen (int,int) ; 
 int /*<<< orphan*/  push_path (char*) ; 
 int snprintf (char*,int,char*,char const*,...) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlink (char*) ; 
 int /*<<< orphan*/  warn (char*) ; 
 int /*<<< orphan*/  warnx (char*) ; 

__attribute__((used)) static int
connect_test(const char *directory_path)
{
	char socket_path[PATH_MAX];
	struct sockaddr_un sun;
	int sock1, sock2;

	sock1 = socket(PF_UNIX, SOCK_STREAM, 0);
	if (sock1 < 0) {
		warn("connect_test: socket(PF_UNIX, SOCK_STREAM, 0)");
		return (-1);
	}

	if (snprintf(socket_path, sizeof(socket_path), "%s/%s",
	    directory_path, SOCK_NAME_TWO) >= PATH_MAX) {
		warn("connect_test: snprintf(socket_path)");
		close(sock1);
		return (-1);
	}

	bzero(&sun, sizeof(sun));
	sun.sun_len = sizeof(sun);
	sun.sun_family = AF_UNIX;
	if (snprintf(sun.sun_path, sizeof(sun.sun_path), "%s", socket_path)
	    >= (int)sizeof(sun.sun_path)) {
		warn("connect_test: snprintf(sun.sun_path)");
		close(sock1);
		return (-1);
	}

	/*
	 * Try connecting to a path that doesn't yet exist.  Should fail with
	 * ENOENT.
	 */
	if (connect(sock1, (struct sockaddr *)&sun, sizeof(sun)) == 0) {
		warnx("connect_test: connect(sun) #1 succeeded");
		close(sock1);
		return (-1);
	}
	if (errno != ENOENT) {
		warn("connect_test: connect(sun) #1");
		close(sock1);
		return (-1);
	}

	if (bind(sock1, (struct sockaddr *)&sun, sizeof(sun)) < 0) {
		warn("connect_test: bind(sun) #1");
		close(sock1);
		return (-1);
	}

	if (listen(sock1, 3) < 0) {
		warn("connect_test: listen(sock1)");
		close(sock1);
		return (-1);
	}

	push_path(socket_path);

	sock2 = socket(PF_UNIX, SOCK_STREAM, 0);
	if (sock2 < 0) {
		warn("socket(PF_UNIX, SOCK_STREAM, 0)");
		close(sock1);
		return (-1);
	}

	/*
	 * Do a simple connect and make sure that works.
	 */
	if (connect(sock2, (struct sockaddr *)&sun, sizeof(sun)) < 0) {
		warn("connect(sun) #2");
		close(sock1);
		return (-1);
	}

	close(sock2);

	close(sock1);

	sock2 = socket(PF_UNIX, SOCK_STREAM, 0);
	if (sock2 < 0) {
		warn("socket(PF_UNIX, SOCK_STREAM, 0)");
		return (-1);
	}

	/*
	 * Confirm that once the listen socket is closed, we get a
	 * connection refused (ECONNREFUSED) when attempting to connect to
	 * the pathname.
	 */
	if (connect(sock2, (struct sockaddr *)&sun, sizeof(sun)) == 0) {
		warnx("connect(sun) #3 succeeded");
		close(sock2);
		return (-1);
	}
	if (errno != ECONNREFUSED) {
		warn("connect(sun) #3");
		close(sock2);
		return (-1);
	}

	close(sock2);
	unlink(socket_path);
	return (0);
}