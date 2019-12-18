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
typedef  int /*<<< orphan*/  u_short ;
struct sockaddr {int dummy; } ;
struct evutil_addrinfo {int ai_addrlen; struct sockaddr* ai_addr; int /*<<< orphan*/  ai_socktype; int /*<<< orphan*/  ai_family; } ;
typedef  int /*<<< orphan*/  strport ;
typedef  int evutil_socket_t ;
typedef  int /*<<< orphan*/  ai ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 scalar_t__ EINPROGRESS ; 
 int NI_MAXSERV ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int WSAEINPROGRESS ; 
 int WSAEINVAL ; 
 int WSAEWOULDBLOCK ; 
 int WSAGetLastError () ; 
 int connect (int,struct sockaddr*,int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  event_err (int,char*) ; 
 int /*<<< orphan*/  event_warn (char*) ; 
 int /*<<< orphan*/  evutil_freeaddrinfo (struct evutil_addrinfo*) ; 
 scalar_t__ evutil_getaddrinfo (char const*,char*,struct evutil_addrinfo*,struct evutil_addrinfo**) ; 
 int /*<<< orphan*/  evutil_make_socket_nonblocking (int) ; 
 int /*<<< orphan*/  evutil_snprintf (char*,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct evutil_addrinfo*,int /*<<< orphan*/ ,int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static evutil_socket_t
http_connect(const char *address, u_short port)
{
	/* Stupid code for connecting */
	struct evutil_addrinfo ai, *aitop;
	char strport[NI_MAXSERV];

	struct sockaddr *sa;
	int slen;
	evutil_socket_t fd;

	memset(&ai, 0, sizeof(ai));
	ai.ai_family = AF_INET;
	ai.ai_socktype = SOCK_STREAM;
	evutil_snprintf(strport, sizeof(strport), "%d", port);
	if (evutil_getaddrinfo(address, strport, &ai, &aitop) != 0) {
		event_warn("getaddrinfo");
		return (-1);
	}
	sa = aitop->ai_addr;
	slen = aitop->ai_addrlen;

	fd = socket(AF_INET, SOCK_STREAM, 0);
	if (fd == -1)
		event_err(1, "socket failed");

	evutil_make_socket_nonblocking(fd);
	if (connect(fd, sa, slen) == -1) {
#ifdef _WIN32
		int tmp_err = WSAGetLastError();
		if (tmp_err != WSAEINPROGRESS && tmp_err != WSAEINVAL &&
		    tmp_err != WSAEWOULDBLOCK)
			event_err(1, "connect failed");
#else
		if (errno != EINPROGRESS)
			event_err(1, "connect failed");
#endif
	}

	evutil_freeaddrinfo(aitop);

	return (fd);
}