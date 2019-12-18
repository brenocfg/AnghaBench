#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct rdma_addrinfo {int /*<<< orphan*/  ai_src_len; int /*<<< orphan*/  ai_src_addr; int /*<<< orphan*/  ai_family; } ;
struct addrinfo {int /*<<< orphan*/  ai_addrlen; int /*<<< orphan*/  ai_addr; int /*<<< orphan*/  ai_family; } ;
struct TYPE_6__ {int /*<<< orphan*/  ai_flags; } ;
struct TYPE_5__ {int /*<<< orphan*/  ai_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  AI_PASSIVE ; 
 int /*<<< orphan*/  RAI_PASSIVE ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_REUSEADDR ; 
 TYPE_3__ ai_hints ; 
 int /*<<< orphan*/  freeaddrinfo (struct addrinfo*) ; 
 char* gai_strerror (int) ; 
 int getaddrinfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*,struct addrinfo**) ; 
 int lrs ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  port ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 TYPE_1__ rai_hints ; 
 int rbind (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rclose (int) ; 
 int /*<<< orphan*/  rdma_freeaddrinfo (struct rdma_addrinfo*) ; 
 int rdma_getaddrinfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,struct rdma_addrinfo**) ; 
 int rlisten (int,int) ; 
 int rsetsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int rsocket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  src_addr ; 
 scalar_t__ use_rgai ; 

__attribute__((used)) static int server_listen(void)
{
	struct rdma_addrinfo *rai = NULL;
	struct addrinfo *ai;
	int val, ret;

	if (use_rgai) {
		rai_hints.ai_flags |= RAI_PASSIVE;
		ret = rdma_getaddrinfo(src_addr, port, &rai_hints, &rai);
	} else {
		ai_hints.ai_flags |= AI_PASSIVE;
		ret = getaddrinfo(src_addr, port, &ai_hints, &ai);
	}
	if (ret) {
		printf("getaddrinfo: %s\n", gai_strerror(ret));
		return ret;
	}

	lrs = rai ? rsocket(rai->ai_family, SOCK_STREAM, 0) :
		    rsocket(ai->ai_family, SOCK_STREAM, 0);
	if (lrs < 0) {
		perror("rsocket");
		ret = lrs;
		goto free;
	}

	val = 1;
	ret = rsetsockopt(lrs, SOL_SOCKET, SO_REUSEADDR, &val, sizeof val);
	if (ret) {
		perror("rsetsockopt SO_REUSEADDR");
		goto close;
	}

	ret = rai ? rbind(lrs, rai->ai_src_addr, rai->ai_src_len) :
		    rbind(lrs, ai->ai_addr, ai->ai_addrlen);
	if (ret) {
		perror("rbind");
		goto close;
	}

	ret = rlisten(lrs, 1);
	if (ret)
		perror("rlisten");

close:
	if (ret)
		rclose(lrs);
free:
	if (rai)
		rdma_freeaddrinfo(rai);
	else
		freeaddrinfo(ai);
	return ret;
}