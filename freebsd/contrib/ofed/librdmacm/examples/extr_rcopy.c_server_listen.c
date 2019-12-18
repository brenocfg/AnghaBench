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
struct addrinfo {int /*<<< orphan*/  ai_addrlen; int /*<<< orphan*/  ai_addr; int /*<<< orphan*/  ai_protocol; int /*<<< orphan*/  ai_socktype; int /*<<< orphan*/  ai_family; int /*<<< orphan*/  ai_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  RAI_PASSIVE ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_REUSEADDR ; 
 int /*<<< orphan*/  freeaddrinfo (struct addrinfo*) ; 
 char* gai_strerror (int) ; 
 int getaddrinfo (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct addrinfo*,struct addrinfo**) ; 
 int /*<<< orphan*/  memset (struct addrinfo*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  port ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int rbind (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rclose (int) ; 
 int rlisten (int,int) ; 
 int rsetsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int rsocket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int server_listen(void)
{
	struct addrinfo hints, *res;
	int ret, rs;

	memset(&hints, 0, sizeof hints);
	hints.ai_flags = RAI_PASSIVE;
 	ret = getaddrinfo(NULL, port, &hints, &res);
	if (ret) {
		printf("getaddrinfo failed: %s\n", gai_strerror(ret));
		return ret;
	}

	rs = rsocket(res->ai_family, res->ai_socktype, res->ai_protocol);
	if (rs < 0) {
		perror("rsocket failed\n");
		ret = rs;
		goto free;
	}

	ret = 1;
	ret = rsetsockopt(rs, SOL_SOCKET, SO_REUSEADDR, &ret, sizeof ret);
	if (ret) {
		perror("rsetsockopt failed");
		goto close;
	}

	ret = rbind(rs, res->ai_addr, res->ai_addrlen);
	if (ret) {
		perror("rbind failed");
		goto close;
	}

	ret = rlisten(rs, 1);
	if (ret) {
		perror("rlisten failed");
		goto close;
	}

	ret = rs;
	goto free;

close:
	rclose(rs);
free:
	freeaddrinfo(res);
	return ret;
}