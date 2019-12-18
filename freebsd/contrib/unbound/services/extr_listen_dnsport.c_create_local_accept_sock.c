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
typedef  int /*<<< orphan*/  usock ;
struct sockaddr_un {unsigned int sun_len; int /*<<< orphan*/  sun_path; int /*<<< orphan*/  sun_family; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  socklen_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_LOCAL ; 
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  TCP_BACKLOG ; 
 int /*<<< orphan*/  VERB_ALGO ; 
 int bind (int,struct sockaddr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  closesocket (int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fd_set_nonblock (int) ; 
 int listen (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_err (char*,...) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (scalar_t__) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int) ; 
 int systemd_get_activated (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ unlink (char const*) ; 
 int /*<<< orphan*/  verbose (int /*<<< orphan*/ ,char*,char const*) ; 

int
create_local_accept_sock(const char *path, int* noproto, int use_systemd)
{
#ifdef HAVE_SYSTEMD
	int ret;

	if (use_systemd && (ret = systemd_get_activated(AF_LOCAL, SOCK_STREAM, 1, NULL, 0, path)) != -1)
		return ret;
	else {
#endif
#ifdef HAVE_SYS_UN_H
	int s;
	struct sockaddr_un usock;
#ifndef HAVE_SYSTEMD
	(void)use_systemd;
#endif

	verbose(VERB_ALGO, "creating unix socket %s", path);
#ifdef HAVE_STRUCT_SOCKADDR_UN_SUN_LEN
	/* this member exists on BSDs, not Linux */
	usock.sun_len = (unsigned)sizeof(usock);
#endif
	usock.sun_family = AF_LOCAL;
	/* length is 92-108, 104 on FreeBSD */
	(void)strlcpy(usock.sun_path, path, sizeof(usock.sun_path));

	if ((s = socket(AF_LOCAL, SOCK_STREAM, 0)) == -1) {
		log_err("Cannot create local socket %s (%s)",
			path, strerror(errno));
		return -1;
	}

	if (unlink(path) && errno != ENOENT) {
		/* The socket already exists and cannot be removed */
		log_err("Cannot remove old local socket %s (%s)",
			path, strerror(errno));
		goto err;
	}

	if (bind(s, (struct sockaddr *)&usock,
		(socklen_t)sizeof(struct sockaddr_un)) == -1) {
		log_err("Cannot bind local socket %s (%s)",
			path, strerror(errno));
		goto err;
	}

	if (!fd_set_nonblock(s)) {
		log_err("Cannot set non-blocking mode");
		goto err;
	}

	if (listen(s, TCP_BACKLOG) == -1) {
		log_err("can't listen: %s", strerror(errno));
		goto err;
	}

	(void)noproto; /*unused*/
	return s;

err:
#ifndef USE_WINSOCK
	close(s);
#else
	closesocket(s);
#endif
	return -1;

#ifdef HAVE_SYSTEMD
	}
#endif
#else
	(void)use_systemd;
	(void)path;
	log_err("Local sockets are not supported");
	*noproto = 1;
	return -1;
#endif
}