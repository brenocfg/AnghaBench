#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct auth_info {void* authlen; void* authtype; } ;
struct TYPE_3__ {void* rok_status; struct auth_info rok_auth; } ;
struct TYPE_4__ {TYPE_1__ rpu_rok; } ;
struct rpc_reply {TYPE_2__ rp_u; } ;
struct rpc_call {void* rp_proc; void* rp_vers; void* rp_prog; void* rp_rpcvers; void* rp_direction; void* rp_xid; } ;
struct iodesc {int /*<<< orphan*/  destport; } ;
struct auth_unix {int dummy; } ;
typedef  int ssize_t ;
typedef  int n_long ;

/* Variables and functions */
 int /*<<< orphan*/  EBADRPC ; 
 int RPCAUTH_NULL ; 
 int RPCAUTH_UNIX ; 
 int RPC_CALL ; 
 int RPC_VER2 ; 
 int /*<<< orphan*/  bzero (char*,int) ; 
 scalar_t__ debug ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (void*) ; 
 void* htonl (int) ; 
 int /*<<< orphan*/  htons (int) ; 
 int ntohl (void*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  recvrpc ; 
 int rpc_getport (struct iodesc*,int,int) ; 
 int rpc_xid ; 
 int sendrecv (struct iodesc*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,void**,void**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sendudp ; 

ssize_t
rpc_call(struct iodesc *d, n_long prog, n_long vers, n_long proc,
	void *sdata, size_t slen, void **rdata, void **pkt)
{
	ssize_t cc, rsize;
	struct auth_info *auth;
	struct rpc_call *call;
	struct rpc_reply *reply;
	char *send_head, *send_tail;
	void *ptr;
	n_long x;
	int port;	/* host order */

#ifdef RPC_DEBUG
	if (debug)
		printf("rpc_call: prog=0x%x vers=%d proc=%d\n",
		    prog, vers, proc);
#endif

	port = rpc_getport(d, prog, vers);
	if (port == -1)
		return (-1);

	d->destport = htons(port);

	/*
	 * Prepend authorization stuff and headers.
	 * Note, must prepend things in reverse order.
	 */
	send_head = sdata;
	send_tail = (char *)sdata + slen;

	/* Auth verifier is always auth_null */
	send_head -= sizeof(*auth);
	auth = (struct auth_info *)send_head;
	auth->authtype = htonl(RPCAUTH_NULL);
	auth->authlen = 0;

	/* Auth credentials: always auth unix (as root) */
	send_head -= sizeof(struct auth_unix);
	bzero(send_head, sizeof(struct auth_unix));
	send_head -= sizeof(*auth);
	auth = (struct auth_info *)send_head;
	auth->authtype = htonl(RPCAUTH_UNIX);
	auth->authlen = htonl(sizeof(struct auth_unix));

	/* RPC call structure. */
	send_head -= sizeof(*call);
	call = (struct rpc_call *)send_head;
	rpc_xid++;
	call->rp_xid       = htonl(rpc_xid);
	call->rp_direction = htonl(RPC_CALL);
	call->rp_rpcvers   = htonl(RPC_VER2);
	call->rp_prog = htonl(prog);
	call->rp_vers = htonl(vers);
	call->rp_proc = htonl(proc);

	ptr = NULL;
	cc = sendrecv(d,
	    sendudp, send_head, send_tail - send_head,
	    recvrpc, &ptr, (void **)&reply, NULL);

#ifdef RPC_DEBUG
	if (debug)
		printf("callrpc: cc=%zd\n", cc);
#endif
	if (cc == -1)
		return (-1);

	if (cc <= sizeof(*reply)) {
		errno = EBADRPC;
		free(ptr);
		return (-1);
	}

	/*
	 * Check the RPC reply status.
	 * The xid, dir, astatus were already checked.
	 */
	auth = &reply->rp_u.rpu_rok.rok_auth;
	x = ntohl(auth->authlen);
	if (x != 0) {
#ifdef RPC_DEBUG
		if (debug)
			printf("callrpc: reply auth != NULL\n");
#endif
		errno = EBADRPC;
		free(ptr);
		return (-1);
	}
	x = ntohl(reply->rp_u.rpu_rok.rok_status);
	if (x != 0) {
		printf("callrpc: error = %ld\n", (long)x);
		errno = EBADRPC;
		free(ptr);
		return (-1);
	}

	rsize = cc - sizeof(*reply);
	*rdata = (void *)((uintptr_t)reply + sizeof(*reply));
	*pkt = ptr;
	return (rsize);
}