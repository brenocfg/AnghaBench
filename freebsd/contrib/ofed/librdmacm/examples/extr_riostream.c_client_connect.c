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
struct rdma_addrinfo {int /*<<< orphan*/  ai_dst_len; int /*<<< orphan*/  ai_dst_addr; int /*<<< orphan*/  ai_family; } ;
struct pollfd {int /*<<< orphan*/  events; void* fd; } ;
struct addrinfo {int /*<<< orphan*/  ai_addrlen; int /*<<< orphan*/  ai_addr; int /*<<< orphan*/  ai_family; } ;
typedef  int socklen_t ;

/* Variables and functions */
 int EINPROGRESS ; 
 int /*<<< orphan*/  POLLOUT ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_ERROR ; 
 int /*<<< orphan*/  ai_hints ; 
 int do_poll (struct pollfd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dst_addr ; 
 int errno ; 
 int /*<<< orphan*/  freeaddrinfo (struct addrinfo*) ; 
 char* gai_strerror (int) ; 
 int getaddrinfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct addrinfo**) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  poll_timeout ; 
 int /*<<< orphan*/  port ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  rai_hints ; 
 int /*<<< orphan*/  rclose (void*) ; 
 int rconnect (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdma_freeaddrinfo (struct rdma_addrinfo*) ; 
 int rdma_getaddrinfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct rdma_addrinfo**) ; 
 int rgetsockopt (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*) ; 
 void* rs ; 
 void* rsocket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_options (void*) ; 
 scalar_t__ use_rgai ; 

__attribute__((used)) static int client_connect(void)
{
	struct rdma_addrinfo *rai = NULL;
	struct addrinfo *ai;
	struct pollfd fds;
	int ret, err;
	socklen_t len;

	ret = use_rgai ? rdma_getaddrinfo(dst_addr, port, &rai_hints, &rai) :
			 getaddrinfo(dst_addr, port, &ai_hints, &ai);
	if (ret) {
		printf("getaddrinfo: %s\n", gai_strerror(ret));
		return ret;
	}

	rs = rai ? rsocket(rai->ai_family, SOCK_STREAM, 0) :
		   rsocket(ai->ai_family, SOCK_STREAM, 0);
	if (rs < 0) {
		perror("rsocket");
		ret = rs;
		goto free;
	}

	set_options(rs);
	/* TODO: bind client to src_addr */

	ret = rai ? rconnect(rs, rai->ai_dst_addr, rai->ai_dst_len) :
		    rconnect(rs, ai->ai_addr, ai->ai_addrlen);
	if (ret && (errno != EINPROGRESS)) {
		perror("rconnect");
		goto close;
	}

	if (ret && (errno == EINPROGRESS)) {
		fds.fd = rs;
		fds.events = POLLOUT;
		ret = do_poll(&fds, poll_timeout);
		if (ret) {
			perror("rpoll");
			goto close;
		}

		len = sizeof err;
		ret = rgetsockopt(rs, SOL_SOCKET, SO_ERROR, &err, &len);
		if (ret)
			goto close;
		if (err) {
			ret = -1;
			errno = err;
			perror("async rconnect");
		}
	}

close:
	if (ret)
		rclose(rs);
free:
	if (rai)
		rdma_freeaddrinfo(rai);
	else
		freeaddrinfo(ai);
	return ret;
}