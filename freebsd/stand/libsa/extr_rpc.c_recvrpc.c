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
typedef  int /*<<< orphan*/  time_t ;
struct TYPE_2__ {int /*<<< orphan*/  rpu_errno; } ;
struct rpc_reply {TYPE_1__ rp_u; int /*<<< orphan*/  rp_astatus; int /*<<< orphan*/  rp_direction; int /*<<< orphan*/  rp_xid; } ;
struct iodesc {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int RPC_MSGACCEPTED ; 
 int RPC_REPLY ; 
 scalar_t__ debug ; 
 int errno ; 
 int /*<<< orphan*/  free (void*) ; 
 int ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int readudp (struct iodesc*,void**,void**,int /*<<< orphan*/ ) ; 
 int rpc_xid ; 

__attribute__((used)) static ssize_t
recvrpc(struct iodesc *d, void **pkt, void **payload, time_t tleft, void *extra)
{
	void *ptr;
	struct rpc_reply *reply;
	ssize_t	n;
	int	x;

	errno = 0;
#ifdef RPC_DEBUG
	if (debug)
		printf("recvrpc: called\n");
#endif

	ptr = NULL;
	n = readudp(d, &ptr, (void **)&reply, tleft);
	if (n <= (4 * 4)) {
		free(ptr);
		return (-1);
	}

	x = ntohl(reply->rp_xid);
	if (x != rpc_xid) {
#ifdef RPC_DEBUG
		if (debug)
			printf("recvrpc: rp_xid %d != xid %d\n", x, rpc_xid);
#endif
		free(ptr);
		return (-1);
	}

	x = ntohl(reply->rp_direction);
	if (x != RPC_REPLY) {
#ifdef RPC_DEBUG
		if (debug)
			printf("recvrpc: rp_direction %d != REPLY\n", x);
#endif
		free(ptr);
		return (-1);
	}

	x = ntohl(reply->rp_astatus);
	if (x != RPC_MSGACCEPTED) {
		errno = ntohl(reply->rp_u.rpu_errno);
		printf("recvrpc: reject, astat=%d, errno=%d\n", x, errno);
		free(ptr);
		return (-1);
	}

	*pkt = ptr;
	*payload = reply;
	/* Return data count (thus indicating success) */
	return (n);
}