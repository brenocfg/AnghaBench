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
struct addrinfo {int /*<<< orphan*/  ai_addrlen; int /*<<< orphan*/  ai_addr; int /*<<< orphan*/  ai_protocol; int /*<<< orphan*/  ai_socktype; int /*<<< orphan*/  ai_family; struct addrinfo* ai_next; } ;
typedef  int /*<<< orphan*/  hostname ;
typedef  int /*<<< orphan*/  hints ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNSPEC ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  EX_OSERR ; 
 int MAXHOSTNAMELEN ; 
 int O_CREAT ; 
 int O_RDONLY ; 
 int O_TRUNC ; 
 int O_WRONLY ; 
 int PMCSTAT_OPEN_FOR_READ ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int S_IRGRP ; 
 int S_IROTH ; 
 int S_IRUSR ; 
 int S_IWUSR ; 
 int accept (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ bind (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ connect (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,char const*,char*,char const*) ; 
 int /*<<< orphan*/  freeaddrinfo (struct addrinfo*) ; 
 char* gai_strerror (int) ; 
 int getaddrinfo (char*,char const*,struct addrinfo*,struct addrinfo**) ; 
 int /*<<< orphan*/  listen (int,int) ; 
 int /*<<< orphan*/  memset (struct addrinfo*,int /*<<< orphan*/ ,int) ; 
 int open (char const*,int,int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * strchr (char const*,char) ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,size_t) ; 
 char* strrchr (char const*,char) ; 

int
pmcstat_open_log(const char *path, int mode)
{
	int error, fd, cfd;
	size_t hlen;
	const char *p, *errstr;
	struct addrinfo hints, *res, *res0;
	char hostname[MAXHOSTNAMELEN];

	errstr = NULL;
	fd = -1;

	/*
	 * If 'path' is "-" then open one of stdin or stdout depending
	 * on the value of 'mode'.
	 *
	 * If 'path' contains a ':' and does not start with a '/' or '.',
	 * and is being opened for writing, treat it as a "host:port"
	 * specification and open a network socket.
	 *
	 * Otherwise, treat 'path' as a file name and open that.
	 */
	if (path[0] == '-' && path[1] == '\0')
		fd = (mode == PMCSTAT_OPEN_FOR_READ) ? 0 : 1;
	else if (path[0] != '/' &&
	    path[0] != '.' && strchr(path, ':') != NULL) {

		p = strrchr(path, ':');
		hlen = p - path;
		if (p == path || hlen >= sizeof(hostname)) {
			errstr = strerror(EINVAL);
			goto done;
		}

		assert(hlen < sizeof(hostname));
		(void) strncpy(hostname, path, hlen);
		hostname[hlen] = '\0';

		(void) memset(&hints, 0, sizeof(hints));
		hints.ai_family = AF_UNSPEC;
		hints.ai_socktype = SOCK_STREAM;
		if ((error = getaddrinfo(hostname, p+1, &hints, &res0)) != 0) {
			errstr = gai_strerror(error);
			goto done;
		}

		fd = -1;
		for (res = res0; res; res = res->ai_next) {
			if ((fd = socket(res->ai_family, res->ai_socktype,
			    res->ai_protocol)) < 0) {
				errstr = strerror(errno);
				continue;
			}
			if (mode == PMCSTAT_OPEN_FOR_READ) {
				if (bind(fd, res->ai_addr, res->ai_addrlen) < 0) {
					errstr = strerror(errno);
					(void) close(fd);
					fd = -1;
					continue;
				}
				listen(fd, 1);
				cfd = accept(fd, NULL, NULL);
				(void) close(fd);
				if (cfd < 0) {
					errstr = strerror(errno);
					fd = -1;
					break;
				}
				fd = cfd;
			} else {
				if (connect(fd, res->ai_addr, res->ai_addrlen) < 0) {
					errstr = strerror(errno);
					(void) close(fd);
					fd = -1;
					continue;
				}
			}
			errstr = NULL;
			break;
		}
		freeaddrinfo(res0);

	} else if ((fd = open(path, mode == PMCSTAT_OPEN_FOR_READ ?
		    O_RDONLY : (O_WRONLY|O_CREAT|O_TRUNC),
		    S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH)) < 0)
			errstr = strerror(errno);

  done:
	if (errstr)
		errx(EX_OSERR, "ERROR: Cannot open \"%s\" for %s: %s.", path,
		    (mode == PMCSTAT_OPEN_FOR_READ ? "reading" : "writing"),
		    errstr);

	return (fd);
}