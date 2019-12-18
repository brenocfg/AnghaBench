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
struct timeval {int tv_sec; int tv_usec; } ;
struct sockaddr {scalar_t__ sa_family; } ;
struct pollfd {int fd; int events; int revents; } ;
struct addrinfo {scalar_t__ ai_family; int ai_addrlen; struct sockaddr const* ai_addr; struct addrinfo* ai_next; } ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  sname ;
typedef  int /*<<< orphan*/  hname ;
typedef  int /*<<< orphan*/  error ;
typedef  int /*<<< orphan*/  bname ;

/* Variables and functions */
 int EBADF ; 
 int EINPROGRESS ; 
 int EINTR ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  F_GETFL ; 
 int /*<<< orphan*/  F_SETFL ; 
 int INFTIM ; 
 int NI_MAXHOST ; 
 int NI_MAXSERV ; 
 int NI_NUMERICHOST ; 
 int NI_NUMERICSERV ; 
 int O_NONBLOCK ; 
 int POLLIN ; 
 int POLLOUT ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_ERROR ; 
 int bind (int,struct sockaddr const*,int) ; 
 struct addrinfo* bindai ; 
 int connect (int,struct sockaddr const*,int) ; 
 int errno ; 
 int fcntl (int,int /*<<< orphan*/ ,int) ; 
 int ftp_poll (struct pollfd*,int,int) ; 
 scalar_t__ getnameinfo (struct sockaddr const*,int,char*,int,char*,int,int) ; 
 int getsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 
 scalar_t__ quit_time ; 
 int /*<<< orphan*/  setupsockbufsize (int) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 
 int /*<<< orphan*/  timersub (struct timeval*,struct timeval*,struct timeval*) ; 
 int /*<<< orphan*/  warn (char*,char*,...) ; 

int
ftp_connect(int sock, const struct sockaddr *name, socklen_t namelen)
{
	int		flags, rv, timeout, error;
	socklen_t	slen;
	struct timeval	endtime, now, td;
	struct pollfd	pfd[1];
	char		hname[NI_MAXHOST];
	char		sname[NI_MAXSERV];

	setupsockbufsize(sock);
	if (getnameinfo(name, namelen,
	    hname, sizeof(hname), sname, sizeof(sname),
	    NI_NUMERICHOST | NI_NUMERICSERV) != 0) {
		strlcpy(hname, "?", sizeof(hname));
		strlcpy(sname, "?", sizeof(sname));
	}

	if (bindai != NULL) {			/* bind to specific addr */
		struct addrinfo *ai;

		for (ai = bindai; ai != NULL; ai = ai->ai_next) {
			if (ai->ai_family == name->sa_family)
				break;
		}
		if (ai == NULL)
			ai = bindai;
		if (bind(sock, ai->ai_addr, ai->ai_addrlen) == -1) {
			char	bname[NI_MAXHOST];
			int	saveerr;

			saveerr = errno;
			if (getnameinfo(ai->ai_addr, ai->ai_addrlen,
			    bname, sizeof(bname), NULL, 0, NI_NUMERICHOST) != 0)
				strlcpy(bname, "?", sizeof(bname));
			errno = saveerr;
			warn("Can't bind to `%s'", bname);
			return -1;
		}
	}

						/* save current socket flags */
	if ((flags = fcntl(sock, F_GETFL, 0)) == -1) {
		warn("Can't %s socket flags for connect to `%s:%s'",
		    "save", hname, sname);
		return -1;
	}
						/* set non-blocking connect */
	if (fcntl(sock, F_SETFL, flags | O_NONBLOCK) == -1) {
		warn("Can't set socket non-blocking for connect to `%s:%s'",
		    hname, sname);
		return -1;
	}

	/* NOTE: we now must restore socket flags on successful exit */

	pfd[0].fd = sock;
	pfd[0].events = POLLIN|POLLOUT;

	if (quit_time > 0) {			/* want a non default timeout */
		(void)gettimeofday(&endtime, NULL);
		endtime.tv_sec += quit_time;	/* determine end time */
	}

	rv = connect(sock, name, namelen);	/* inititate the connection */
	if (rv == -1) {				/* connection error */
		if (errno != EINPROGRESS) {	/* error isn't "please wait" */
 connecterror:
			warn("Can't connect to `%s:%s'", hname, sname);
			return -1;
		}

						/* connect EINPROGRESS; wait */
		do {
			if (quit_time > 0) {	/* determine timeout */
				(void)gettimeofday(&now, NULL);
				timersub(&endtime, &now, &td);
				timeout = td.tv_sec * 1000 + td.tv_usec/1000;
				if (timeout < 0)
					timeout = 0;
			} else {
				timeout = INFTIM;
			}
			pfd[0].revents = 0;
			rv = ftp_poll(pfd, 1, timeout);
						/* loop until poll ! EINTR */
		} while (rv == -1 && errno == EINTR);

		if (rv == 0) {			/* poll (connect) timed out */
			errno = ETIMEDOUT;
			goto connecterror;
		}

		if (rv == -1) {			/* poll error */
			goto connecterror;
		} else if (pfd[0].revents & (POLLIN|POLLOUT)) {
			slen = sizeof(error);	/* OK, or pending error */
			if (getsockopt(sock, SOL_SOCKET, SO_ERROR,
			    &error, &slen) == -1) {
						/* Solaris pending error */
				goto connecterror;
			} else if (error != 0) {
				errno = error;	/* BSD pending error */
				goto connecterror;
			}
		} else {
			errno = EBADF;		/* this shouldn't happen ... */
			goto connecterror;
		}
	}

	if (fcntl(sock, F_SETFL, flags) == -1) {
						/* restore socket flags */
		warn("Can't %s socket flags for connect to `%s:%s'",
		    "restore", hname, sname);
		return -1;
	}
	return 0;
}