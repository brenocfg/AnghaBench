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
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sockaddr {int dummy; } ;
struct rsocket {scalar_t__ type; scalar_t__ state; int /*<<< orphan*/  slock; int /*<<< orphan*/  conn_dest; int /*<<< orphan*/  udp_sock; TYPE_3__* cm_id; } ;
typedef  int /*<<< orphan*/  socklen_t ;
struct TYPE_4__ {int /*<<< orphan*/  dst_addr; } ;
struct TYPE_5__ {TYPE_1__ addr; } ;
struct TYPE_6__ {TYPE_2__ route; } ;

/* Variables and functions */
 int /*<<< orphan*/  EBADF ; 
 int ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ SOCK_STREAM ; 
 int connect (int /*<<< orphan*/ ,struct sockaddr const*,int /*<<< orphan*/ ) ; 
 int ds_get_dest (struct rsocket*,struct sockaddr const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ds_init_ep (struct rsocket*) ; 
 int /*<<< orphan*/  fastlock_acquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fastlock_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  idm ; 
 struct rsocket* idm_lookup (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct sockaddr const*,int /*<<< orphan*/ ) ; 
 int rs_do_connect (struct rsocket*) ; 
 scalar_t__ rs_init ; 

int rconnect(int socket, const struct sockaddr *addr, socklen_t addrlen)
{
	struct rsocket *rs;
	int ret;

	rs = idm_lookup(&idm, socket);
	if (!rs)
		return ERR(EBADF);
	if (rs->type == SOCK_STREAM) {
		memcpy(&rs->cm_id->route.addr.dst_addr, addr, addrlen);
		ret = rs_do_connect(rs);
	} else {
		if (rs->state == rs_init) {
			ret = ds_init_ep(rs);
			if (ret)
				return ret;
		}

		fastlock_acquire(&rs->slock);
		ret = connect(rs->udp_sock, addr, addrlen);
		if (!ret)
			ret = ds_get_dest(rs, addr, addrlen, &rs->conn_dest);
		fastlock_release(&rs->slock);
	}
	return ret;
}