#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  s6_addr; } ;
struct TYPE_12__ {TYPE_4__ sin6_addr; } ;
struct TYPE_9__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_10__ {TYPE_2__ sin_addr; } ;
struct TYPE_8__ {int /*<<< orphan*/  sa_family; } ;
union socket_addr {TYPE_5__ sin6; TYPE_3__ sin; TYPE_1__ sa; } ;
struct message {int op; size_t id; int /*<<< orphan*/  data; } ;
typedef  size_t ssize_t ;
typedef  int /*<<< orphan*/  socklen_t ;
struct TYPE_13__ {int /*<<< orphan*/  recvcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  AF_INET6 ; 
 TYPE_6__* clients ; 
 int /*<<< orphan*/  htobe32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  id ; 
 char* inet_ntop (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  memset (TYPE_6__*,int /*<<< orphan*/ ,int) ; 
#define  msg_op_echo 131 
#define  msg_op_end 130 
#define  msg_op_login 129 
#define  msg_op_start 128 
 int /*<<< orphan*/  printf (char*,char*) ; 
 size_t svr_send (struct message*,size_t,union socket_addr*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int svr_process(struct message *msg, size_t size,
		       union socket_addr *addr, socklen_t addrlen)
{
	char str[64];
	ssize_t ret;

	switch (msg->op) {
	case msg_op_login:
		if (addr->sa.sa_family == AF_INET) {
			printf("client login from %s\n",
			       inet_ntop(AF_INET, &addr->sin.sin_addr.s_addr,
					 str, sizeof str));
		} else {
			printf("client login from %s\n",
			       inet_ntop(AF_INET6, &addr->sin6.sin6_addr.s6_addr,
					 str, sizeof str));
		}
		msg->id = id++;
		/* fall through */
	case msg_op_start:
		memset(&clients[msg->id], 0, sizeof clients[msg->id]);
		break;
	case msg_op_echo:
		clients[msg->id].recvcnt++;
		break;
	case msg_op_end:
		msg->data = htobe32(clients[msg->id].recvcnt);
		break;
	default:
		clients[msg->id].recvcnt++;
		return 0;
	}

	ret = svr_send(msg, size, addr, addrlen);
	return (ret == size) ? 0 : (int) ret;
}