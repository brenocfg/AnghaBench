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
struct addrinfo {int /*<<< orphan*/  ai_addrlen; int /*<<< orphan*/  ai_addr; int /*<<< orphan*/  ai_protocol; int /*<<< orphan*/  ai_socktype; int /*<<< orphan*/  ai_family; struct addrinfo* ai_next; int /*<<< orphan*/  ai_flags; } ;
struct TYPE_2__ {int num_clients; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  AI_PASSIVE ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_REUSEADDR ; 
 int accept (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ asprintf (char**,char*,int) ; 
 int /*<<< orphan*/  bind (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ connect_qps (int) ; 
 TYPE_1__ ctx ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  freeaddrinfo_null (struct addrinfo*) ; 
 char* gai_strerror (int) ; 
 int getaddrinfo (int /*<<< orphan*/ *,char*,struct addrinfo*,struct addrinfo**) ; 
 int /*<<< orphan*/  listen (int,int) ; 
 scalar_t__ recv_remote_dest (int,int) ; 
 scalar_t__ send_local_dest (int,int) ; 
 int /*<<< orphan*/  setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int pp_server_connect(int port)
{
	struct addrinfo *res, *t;
	char *service;
	int ret, i, n;
	int sockfd = -1, connfd;
	struct addrinfo hints = {
		.ai_flags    = AI_PASSIVE,
		.ai_family   = AF_INET,
		.ai_socktype = SOCK_STREAM
	};

	if (asprintf(&service, "%d", port) < 0)
		return 1;

	ret = getaddrinfo(NULL, service, &hints, &res);
	if (ret < 0) {
		fprintf(stderr, "%s for port %d\n", gai_strerror(ret), port);
		free(service);
		return 1;
	}

	for (t = res; t; t = t->ai_next) {
		sockfd = socket(t->ai_family, t->ai_socktype, t->ai_protocol);
		if (sockfd >= 0) {
			n = 1;
			setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &n, sizeof n);
			if (!bind(sockfd, t->ai_addr, t->ai_addrlen))
				break;
			close(sockfd);
			sockfd = -1;
		}
	}

	freeaddrinfo_null(res);
	free(service);

	if (sockfd < 0) {
		fprintf(stderr, "Couldn't listen to port %d\n", port);
		return 1;
	}

	listen(sockfd, ctx.num_clients);

	for (i = 0; i < ctx.num_clients; i++) {
		connfd = accept(sockfd, NULL, NULL);
		if (connfd < 0) {
			fprintf(stderr, "accept() failed for client %d\n", i);
			return 1;
		}

		if (recv_remote_dest(connfd, i))
			return 1;

		if (send_local_dest(connfd, i))
			return 1;

		if (connect_qps(i))
			return 1;
	}

	close(sockfd);
	return 0;
}