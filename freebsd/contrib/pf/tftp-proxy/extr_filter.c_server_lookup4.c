#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int8_t ;
struct TYPE_8__ {int /*<<< orphan*/  v4; } ;
struct TYPE_7__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_6__ {int /*<<< orphan*/  v4; } ;
struct TYPE_5__ {int /*<<< orphan*/  v4; } ;
struct sockaddr_in {int sin_len; int /*<<< orphan*/  rdport; int /*<<< orphan*/  sin_port; TYPE_4__ rdaddr; TYPE_3__ sin_addr; void* sin_family; int /*<<< orphan*/  dport; int /*<<< orphan*/  sport; TYPE_2__ daddr; TYPE_1__ saddr; int /*<<< orphan*/  proto; void* af; int /*<<< orphan*/  direction; } ;
struct pfioc_natlook {int sin_len; int /*<<< orphan*/  rdport; int /*<<< orphan*/  sin_port; TYPE_4__ rdaddr; TYPE_3__ sin_addr; void* sin_family; int /*<<< orphan*/  dport; int /*<<< orphan*/  sport; TYPE_2__ daddr; TYPE_1__ saddr; int /*<<< orphan*/  proto; void* af; int /*<<< orphan*/  direction; } ;

/* Variables and functions */
 void* AF_INET ; 
 int /*<<< orphan*/  DIOCNATLOOK ; 
 int /*<<< orphan*/  PF_OUT ; 
 int /*<<< orphan*/  dev ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sockaddr_in*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (struct sockaddr_in*,int /*<<< orphan*/ ,int) ; 

int
server_lookup4(struct sockaddr_in *client, struct sockaddr_in *proxy,
    struct sockaddr_in *server, u_int8_t proto)
{
	struct pfioc_natlook pnl;

	memset(&pnl, 0, sizeof pnl);
	pnl.direction = PF_OUT;
	pnl.af = AF_INET;
	pnl.proto = proto;
	memcpy(&pnl.saddr.v4, &client->sin_addr.s_addr, sizeof pnl.saddr.v4);
	memcpy(&pnl.daddr.v4, &proxy->sin_addr.s_addr, sizeof pnl.daddr.v4);
	pnl.sport = client->sin_port;
	pnl.dport = proxy->sin_port;

	if (ioctl(dev, DIOCNATLOOK, &pnl) == -1)
		return (-1);

	memset(server, 0, sizeof(struct sockaddr_in));
	server->sin_len = sizeof(struct sockaddr_in);
	server->sin_family = AF_INET;
	memcpy(&server->sin_addr.s_addr, &pnl.rdaddr.v4,
	    sizeof server->sin_addr.s_addr);
	server->sin_port = pnl.rdport;

	return (0);
}