#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct addrinfo {int /*<<< orphan*/  ai_addrlen; int /*<<< orphan*/  ai_addr; int /*<<< orphan*/  ai_protocol; int /*<<< orphan*/  ai_socktype; int /*<<< orphan*/  ai_family; } ;
struct TYPE_3__ {int /*<<< orphan*/  op; } ;

/* Variables and functions */
 int CTRL_MSG_SIZE ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int client_send_recv (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  dst_addr ; 
 int /*<<< orphan*/  freeaddrinfo (struct addrinfo*) ; 
 TYPE_1__ g_msg ; 
 char* gai_strerror (int) ; 
 int getaddrinfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct addrinfo*,struct addrinfo**) ; 
 int /*<<< orphan*/  memset (struct addrinfo*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msg_op_login ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  port ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int rs ; 
 int /*<<< orphan*/  rs_close (int) ; 
 int rs_connect (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rs_socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_options (int) ; 

__attribute__((used)) static int client_connect(void)
{
	struct addrinfo hints, *res;
	int ret;

	memset(&hints, 0, sizeof hints);
	hints.ai_socktype = SOCK_DGRAM;
 	ret = getaddrinfo(dst_addr, port, &hints, &res);
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
	ret = rs_connect(rs, res->ai_addr, res->ai_addrlen);
	if (ret) {
		perror("rconnect");
		rs_close(rs);
		goto out;
	}

	g_msg.op = msg_op_login;
	ret = client_send_recv(&g_msg, CTRL_MSG_SIZE, 1000);
	if (ret == CTRL_MSG_SIZE)
		ret = 0;

out:
	freeaddrinfo(res);
	return ret;
}