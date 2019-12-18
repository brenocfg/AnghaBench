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
struct rsocket {scalar_t__ type; int /*<<< orphan*/  udp_sock; int /*<<< orphan*/  cm_id; } ;
typedef  int /*<<< orphan*/  socklen_t ;

/* Variables and functions */
 int /*<<< orphan*/  EBADF ; 
 int ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ SOCK_STREAM ; 
 int getsockname (int /*<<< orphan*/ ,struct sockaddr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  idm ; 
 struct rsocket* idm_lookup (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rdma_get_local_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rs_copy_addr (struct sockaddr*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int rgetsockname(int socket, struct sockaddr *addr, socklen_t *addrlen)
{
	struct rsocket *rs;

	rs = idm_lookup(&idm, socket);
	if (!rs)
		return ERR(EBADF);
	if (rs->type == SOCK_STREAM) {
		rs_copy_addr(addr, rdma_get_local_addr(rs->cm_id), addrlen);
		return 0;
	} else {
		return getsockname(rs->udp_sock, addr, addrlen);
	}
}