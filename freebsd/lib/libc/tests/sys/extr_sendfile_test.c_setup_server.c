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
struct sockaddr {int dummy; } ;
struct addrinfo {int ai_family; int ai_socktype; int /*<<< orphan*/  ai_addrlen; scalar_t__ ai_addr; int /*<<< orphan*/  ai_protocol; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_REQUIRE_EQ_MSG (int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NI_MAXHOST ; 
 int /*<<< orphan*/  NI_NUMERICHOST ; 
 int bind (int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  freeaddrinfo (struct addrinfo*) ; 
 int /*<<< orphan*/  gai_strerror (int) ; 
 int getnameinfo (struct sockaddr const*,int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int listen (int,int) ; 
 int make_socket (int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ nitems (char*) ; 
 int /*<<< orphan*/  printf (char*,char*,int,int) ; 
 int /*<<< orphan*/  resolve_localhost (struct addrinfo**,int,int,int) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
setup_server(int domain, int type, int port)
{
	struct addrinfo *res;
	char host[NI_MAXHOST+1];
	int error, sock;

	resolve_localhost(&res, domain, type, port);
	sock = make_socket(res->ai_family, res->ai_socktype, res->ai_protocol);

	error = getnameinfo(
	    (const struct sockaddr*)res->ai_addr, res->ai_addrlen,
	    host, nitems(host) - 1, NULL, 0, NI_NUMERICHOST);
	ATF_REQUIRE_EQ_MSG(error, 0,
	    "getnameinfo failed: %s", gai_strerror(error));
	printf(
	    "Will try to bind socket to host='%s', address_family=%d, "
	    "socket_type=%d\n",
	    host, res->ai_family, res->ai_socktype);
	/* Avoid a double print when forked by flushing. */
	fflush(stdout);
	error = bind(sock, res->ai_addr, res->ai_addrlen);
	freeaddrinfo(res);
	ATF_REQUIRE_EQ_MSG(error, 0, "bind failed: %s", strerror(errno));
	error = listen(sock, 1);
	ATF_REQUIRE_EQ_MSG(error, 0, "listen failed: %s", strerror(errno));

	return (sock);
}