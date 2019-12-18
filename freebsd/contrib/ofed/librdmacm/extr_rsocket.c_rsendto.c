#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sockaddr {int dummy; } ;
struct rsocket {scalar_t__ type; scalar_t__ state; int /*<<< orphan*/  slock; TYPE_1__* conn_dest; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  socklen_t ;
struct TYPE_2__ {int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  EISCONN ; 
 int ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ SOCK_STREAM ; 
 scalar_t__ ds_compare_addr (struct sockaddr const*,int /*<<< orphan*/ *) ; 
 int ds_get_dest (struct rsocket*,struct sockaddr const*,int /*<<< orphan*/ ,TYPE_1__**) ; 
 int ds_init_ep (struct rsocket*) ; 
 int dsend (struct rsocket*,void const*,size_t,int) ; 
 int /*<<< orphan*/  fastlock_acquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fastlock_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  idm ; 
 struct rsocket* idm_at (int /*<<< orphan*/ *,int) ; 
 scalar_t__ rs_init ; 
 int rsend (int,void const*,size_t,int) ; 

ssize_t rsendto(int socket, const void *buf, size_t len, int flags,
		const struct sockaddr *dest_addr, socklen_t addrlen)
{
	struct rsocket *rs;
	int ret;

	rs = idm_at(&idm, socket);
	if (rs->type == SOCK_STREAM) {
		if (dest_addr || addrlen)
			return ERR(EISCONN);

		return rsend(socket, buf, len, flags);
	}

	if (rs->state == rs_init) {
		ret = ds_init_ep(rs);
		if (ret)
			return ret;
	}

	fastlock_acquire(&rs->slock);
	if (!rs->conn_dest || ds_compare_addr(dest_addr, &rs->conn_dest->addr)) {
		ret = ds_get_dest(rs, dest_addr, addrlen, &rs->conn_dest);
		if (ret)
			goto out;
	}

	ret = dsend(rs, buf, len, flags);
out:
	fastlock_release(&rs->slock);
	return ret;
}