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
typedef  int /*<<< orphan*/  thisaddr_ss ;
typedef  int /*<<< orphan*/  thataddr_ss ;
struct sockaddr_storage {int dummy; } ;
typedef  struct sockaddr sockaddr ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  one ;
typedef  int /*<<< orphan*/  fd_set ;
typedef  int /*<<< orphan*/  erraddr_ss ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int BUFSIZ ; 
 scalar_t__ EINTR ; 
 scalar_t__ FD_ISSET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_SET (int,int /*<<< orphan*/ *) ; 
 int FD_SETSIZE ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_DEBUG ; 
 int /*<<< orphan*/  STDOUT_FILENO ; 
 int accept (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 scalar_t__ getpeername (int,struct sockaddr*,int*) ; 
 scalar_t__ getsockname (int,struct sockaddr*,int*) ; 
 scalar_t__ listen (int,int) ; 
 scalar_t__ max (int,int) ; 
 int net_read (int,char*,int) ; 
 int net_write (int,char*,int) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 int read (int,char*,int) ; 
 int rsh_loop (int,int) ; 
 int select (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 scalar_t__ sock_debug ; 
 int /*<<< orphan*/  socket_get_port (struct sockaddr*) ; 
 int strlen (char*) ; 
 int stub1 (int,struct sockaddr*,struct sockaddr*,char const*,char const*,char const*,size_t,char const*) ; 
 int /*<<< orphan*/  warn (char*,...) ; 
 int /*<<< orphan*/  warnx (char*,...) ; 
 int /*<<< orphan*/  write (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int
proto (int s, int errsock,
       const char *hostname, const char *local_user, const char *remote_user,
       const char *cmd, size_t cmd_len,
       int (*auth_func)(int s,
			struct sockaddr *this, struct sockaddr *that,
			const char *hostname, const char *remote_user,
			const char *local_user, size_t cmd_len,
			const char *cmd))
{
    int errsock2;
    char buf[BUFSIZ];
    char *p;
    size_t len;
    char reply;
    struct sockaddr_storage thisaddr_ss;
    struct sockaddr *thisaddr = (struct sockaddr *)&thisaddr_ss;
    struct sockaddr_storage thataddr_ss;
    struct sockaddr *thataddr = (struct sockaddr *)&thataddr_ss;
    struct sockaddr_storage erraddr_ss;
    struct sockaddr *erraddr = (struct sockaddr *)&erraddr_ss;
    socklen_t addrlen;
    int ret;

    addrlen = sizeof(thisaddr_ss);
    if (getsockname (s, thisaddr, &addrlen) < 0) {
	warn ("getsockname(%s)", hostname);
	return 1;
    }
    addrlen = sizeof(thataddr_ss);
    if (getpeername (s, thataddr, &addrlen) < 0) {
	warn ("getpeername(%s)", hostname);
	return 1;
    }

    if (errsock != -1) {

	addrlen = sizeof(erraddr_ss);
	if (getsockname (errsock, erraddr, &addrlen) < 0) {
	    warn ("getsockname");
	    return 1;
	}

	if (listen (errsock, 1) < 0) {
	    warn ("listen");
	    return 1;
	}

	p = buf;
	snprintf (p, sizeof(buf), "%u",
		  ntohs(socket_get_port(erraddr)));
	len = strlen(buf) + 1;
	if(net_write (s, buf, len) != len) {
	    warn ("write");
	    close (errsock);
	    return 1;
	}


	for (;;) {
	    fd_set fdset;

	    if (errsock >= FD_SETSIZE || s >= FD_SETSIZE)
		errx (1, "fd too large");

	    FD_ZERO(&fdset);
	    FD_SET(errsock, &fdset);
	    FD_SET(s, &fdset);

	    ret = select (max(errsock, s) + 1, &fdset, NULL, NULL, NULL);
	    if (ret < 0) {
		if (errno == EINTR)
		    continue;
		warn ("select");
		close (errsock);
		return 1;
	    }
	    if (FD_ISSET(errsock, &fdset)) {
		errsock2 = accept (errsock, NULL, NULL);
		close (errsock);
		if (errsock2 < 0) {
		    warn ("accept");
		    return 1;
		}
		break;
	    }

	    /*
	     * there should not arrive any data on this fd so if it's
	     * readable it probably indicates that the other side when
	     * away.
	     */

	    if (FD_ISSET(s, &fdset)) {
		warnx ("socket closed");
		close (errsock);
		errsock2 = -1;
		break;
	    }
	}
    } else {
	if (net_write (s, "0", 2) != 2) {
	    warn ("write");
	    return 1;
	}
	errsock2 = -1;
    }

    if ((*auth_func)(s, thisaddr, thataddr, hostname,
		     remote_user, local_user,
		     cmd_len, cmd)) {
	close (errsock2);
	return 1;
    }

    ret = net_read (s, &reply, 1);
    if (ret < 0) {
	warn ("read");
	close (errsock2);
	return 1;
    } else if (ret == 0) {
	warnx ("unexpected EOF from %s", hostname);
	close (errsock2);
	return 1;
    }
    if (reply != 0) {

	warnx ("Error from rshd at %s:", hostname);

	while ((ret = read (s, buf, sizeof(buf))) > 0)
	    write (STDOUT_FILENO, buf, ret);
        write (STDOUT_FILENO,"\n",1);
	close (errsock2);
	return 1;
    }

    if (sock_debug) {
	int one = 1;
	if (setsockopt(s, SOL_SOCKET, SO_DEBUG, (void *)&one, sizeof(one)) < 0)
	    warn("setsockopt remote");
	if (errsock2 != -1 &&
	    setsockopt(errsock2, SOL_SOCKET, SO_DEBUG,
		       (void *)&one, sizeof(one)) < 0)
	    warn("setsockopt stderr");
    }

    return rsh_loop (s, errsock2);
}