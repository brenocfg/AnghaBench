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
struct sockaddr {int dummy; } ;
struct rsocket {scalar_t__ type; int /*<<< orphan*/  rlock; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  socklen_t ;

/* Variables and functions */
 scalar_t__ SOCK_DGRAM ; 
 int ds_recvfrom (struct rsocket*,void*,size_t,int,struct sockaddr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fastlock_acquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fastlock_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  idm ; 
 struct rsocket* idm_at (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rgetpeername (int,struct sockaddr*,int /*<<< orphan*/ *) ; 
 int rrecv (int,void*,size_t,int) ; 

ssize_t rrecvfrom(int socket, void *buf, size_t len, int flags,
		  struct sockaddr *src_addr, socklen_t *addrlen)
{
	struct rsocket *rs;
	int ret;

	rs = idm_at(&idm, socket);
	if (rs->type == SOCK_DGRAM) {
		fastlock_acquire(&rs->rlock);
		ret = ds_recvfrom(rs, buf, len, flags, src_addr, addrlen);
		fastlock_release(&rs->rlock);
		return ret;
	}

	ret = rrecv(socket, buf, len, flags);
	if (ret > 0 && src_addr)
		rgetpeername(socket, src_addr, addrlen);

	return ret;
}