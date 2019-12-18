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

/* Variables and functions */
 int /*<<< orphan*/  AF_UNSPEC ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 scalar_t__ asprintf (char**,char*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  connect (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ connect_qps (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  freeaddrinfo_null (struct addrinfo*) ; 
 char* gai_strerror (int) ; 
 int getaddrinfo (char const*,char*,struct addrinfo*,struct addrinfo**) ; 
 scalar_t__ recv_remote_dest (int,int /*<<< orphan*/ ) ; 
 scalar_t__ send_local_dest (int,int /*<<< orphan*/ ) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int pp_client_connect(const char *servername, int port)
{
	struct addrinfo *res, *t;
	char *service;
	int ret;
	int sockfd = -1;
	struct addrinfo hints = {
		.ai_family   = AF_UNSPEC,
		.ai_socktype = SOCK_STREAM
	};

	if (asprintf(&service, "%d", port) < 0)
		return 1;

	ret = getaddrinfo(servername, service, &hints, &res);
	if (ret < 0) {
		fprintf(stderr, "%s for %s:%d\n", gai_strerror(ret), servername, port);
		free(service);
		return 1;
	}

	for (t = res; t; t = t->ai_next) {
		sockfd = socket(t->ai_family, t->ai_socktype, t->ai_protocol);
		if (sockfd >= 0) {
			if (!connect(sockfd, t->ai_addr, t->ai_addrlen))
				break;
			close(sockfd);
			sockfd = -1;
		}
	}

	freeaddrinfo_null(res);
	free(service);

	if (sockfd < 0) {
		fprintf(stderr, "Couldn't connect to %s:%d\n", servername, port);
		return 1;
	}

	if (send_local_dest(sockfd, 0))
		return 1;

	if (recv_remote_dest(sockfd, 0))
		return 1;

	if (connect_qps(0))
		return 1;

	return 0;
}