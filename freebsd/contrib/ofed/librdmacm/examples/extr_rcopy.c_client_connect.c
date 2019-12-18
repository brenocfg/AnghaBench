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
struct addrinfo {int /*<<< orphan*/  ai_addrlen; int /*<<< orphan*/  ai_addr; int /*<<< orphan*/  ai_protocol; int /*<<< orphan*/  ai_socktype; int /*<<< orphan*/  ai_family; } ;

/* Variables and functions */
 int /*<<< orphan*/  dst_addr ; 
 int /*<<< orphan*/  freeaddrinfo (struct addrinfo*) ; 
 char* gai_strerror (int) ; 
 int getaddrinfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct addrinfo**) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  port ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  rclose (int) ; 
 int rconnect (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rsocket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int client_connect(void)
{
	struct addrinfo *res;
	int ret, rs;

 	ret = getaddrinfo(dst_addr, port, NULL, &res);
	if (ret) {
		printf("getaddrinfo failed: %s\n", gai_strerror(ret));
		return ret;
	}

	rs = rsocket(res->ai_family, res->ai_socktype, res->ai_protocol);
	if (rs < 0) {
		perror("rsocket failed\n");
		goto free;
	}

	ret = rconnect(rs, res->ai_addr, res->ai_addrlen);
	if (ret) {
		perror("rconnect failed\n");
		rclose(rs);
		rs = ret;
	}

free:
	freeaddrinfo(res);
	return rs;
}