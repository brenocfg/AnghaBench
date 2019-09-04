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
struct addrinfo {int ai_socktype; scalar_t__ ai_addrlen; int /*<<< orphan*/  ai_addr; int /*<<< orphan*/  ai_protocol; int /*<<< orphan*/  ai_family; struct addrinfo* ai_next; } ;
typedef  int /*<<< orphan*/  socklen_t ;
typedef  int /*<<< orphan*/  git_stream ;
struct TYPE_2__ {scalar_t__ s; int /*<<< orphan*/  host; int /*<<< orphan*/  port; } ;
typedef  TYPE_1__ git_socket_stream ;
typedef  scalar_t__ GIT_SOCKET ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNSPEC ; 
 int /*<<< orphan*/  GIT_ERROR_NET ; 
 int /*<<< orphan*/  GIT_ERROR_OS ; 
 scalar_t__ INVALID_SOCKET ; 
 int SOCK_CLOEXEC ; 
 int SOCK_STREAM ; 
 int /*<<< orphan*/  close_socket (scalar_t__) ; 
 scalar_t__ connect (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  memset (struct addrinfo*,int,int) ; 
 int /*<<< orphan*/  p_freeaddrinfo (struct addrinfo*) ; 
 int /*<<< orphan*/  p_gai_strerror (int) ; 
 int p_getaddrinfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct addrinfo*,struct addrinfo**) ; 
 scalar_t__ socket (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int socket_connect(git_stream *stream)
{
	struct addrinfo *info = NULL, *p;
	struct addrinfo hints;
	git_socket_stream *st = (git_socket_stream *) stream;
	GIT_SOCKET s = INVALID_SOCKET;
	int ret;

#ifdef GIT_WIN32
	/* on win32, the WSA context needs to be initialized
	 * before any socket calls can be performed */
	WSADATA wsd;

	if (WSAStartup(MAKEWORD(2,2), &wsd) != 0) {
		git_error_set(GIT_ERROR_OS, "winsock init failed");
		return -1;
	}

	if (LOBYTE(wsd.wVersion) != 2 || HIBYTE(wsd.wVersion) != 2) {
		WSACleanup();
		git_error_set(GIT_ERROR_OS, "winsock init failed");
		return -1;
	}
#endif

	memset(&hints, 0x0, sizeof(struct addrinfo));
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_family = AF_UNSPEC;

	if ((ret = p_getaddrinfo(st->host, st->port, &hints, &info)) != 0) {
		git_error_set(GIT_ERROR_NET,
			   "failed to resolve address for %s: %s", st->host, p_gai_strerror(ret));
		return -1;
	}

	for (p = info; p != NULL; p = p->ai_next) {
		s = socket(p->ai_family, p->ai_socktype | SOCK_CLOEXEC, p->ai_protocol);

		if (s == INVALID_SOCKET)
			continue;

		if (connect(s, p->ai_addr, (socklen_t)p->ai_addrlen) == 0)
			break;

		/* If we can't connect, try the next one */
		close_socket(s);
		s = INVALID_SOCKET;
	}

	/* Oops, we couldn't connect to any address */
	if (s == INVALID_SOCKET && p == NULL) {
		git_error_set(GIT_ERROR_OS, "failed to connect to %s", st->host);
		p_freeaddrinfo(info);
		return -1;
	}

	st->s = s;
	p_freeaddrinfo(info);
	return 0;
}