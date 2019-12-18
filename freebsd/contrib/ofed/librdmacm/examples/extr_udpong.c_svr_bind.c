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
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  free (struct addrinfo*) ; 
 char* gai_strerror (int) ; 
 int getaddrinfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct addrinfo*,struct addrinfo**) ; 
 int /*<<< orphan*/  memset (struct addrinfo*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  port ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int rs ; 
 int rs_bind (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rs_close (int) ; 
 int rs_socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_options (int) ; 
 int /*<<< orphan*/  src_addr ; 

__attribute__((used)) static int svr_bind(void)
{
	struct addrinfo hints, *res;
	int ret;

	memset(&hints, 0, sizeof hints);
	hints.ai_socktype = SOCK_DGRAM;
 	ret = getaddrinfo(src_addr, port, &hints, &res);
	if (ret) {
		printf("getaddrinfo: %s\n", gai_strerror(ret));
		return ret;
	}

	rs = rs_socket(res->ai_family, res->ai_socktype, res->ai_protocol);
	if (rs < 0) {
		perror("rsocket");
		ret = rs;
		goto out;
	}

	set_options(rs);
	ret = rs_bind(rs, res->ai_addr, res->ai_addrlen);
	if (ret) {
		perror("rbind");
		rs_close(rs);
	}

out:
	free(res);
	return ret;
}