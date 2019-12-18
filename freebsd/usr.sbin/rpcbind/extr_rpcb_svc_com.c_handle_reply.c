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
typedef  scalar_t__ xdrproc_t ;
typedef  int /*<<< orphan*/  u_int ;
struct sockaddr_storage {int dummy; } ;
struct sockaddr {int dummy; } ;
struct TYPE_4__ {scalar_t__ proc; scalar_t__ where; } ;
struct TYPE_5__ {TYPE_1__ ar_results; int /*<<< orphan*/  ar_verf; } ;
struct rpc_msg {int rm_xid; TYPE_2__ acpted_rply; } ;
struct rpc_err {scalar_t__ re_status; } ;
struct TYPE_6__ {char* args; int arglen; } ;
struct r_rmtcall_args {char* rmt_uaddr; int /*<<< orphan*/  rmt_localvers; TYPE_3__ rmt_args; } ;
struct finfo {char* uaddr; int /*<<< orphan*/  versnum; } ;
typedef  int /*<<< orphan*/  ss ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  XDR ;
typedef  int /*<<< orphan*/  SVCXPRT ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  RPC_BUF_MAX ; 
 scalar_t__ RPC_SUCCESS ; 
 int /*<<< orphan*/  XDR_DECODE ; 
 int XDR_GETPOS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _null_auth ; 
 int /*<<< orphan*/  _seterr_reply (struct rpc_msg*,struct rpc_err*) ; 
 char* clnt_sperrno (scalar_t__) ; 
 scalar_t__ debugging ; 
 scalar_t__ errno ; 
 struct finfo* forward_find (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  free_slot_by_xid (int) ; 
 char* malloc (int /*<<< orphan*/ ) ; 
 int recvfrom (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sockaddr*,int*) ; 
 int /*<<< orphan*/  rpcbind_get_conf (char*) ; 
 int /*<<< orphan*/  send_svcsyserr (int /*<<< orphan*/ *,struct finfo*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  svc_getrpccaller (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svc_sendreply (int /*<<< orphan*/ *,scalar_t__,char*) ; 
 char* taddr2uaddr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdr_replymsg (int /*<<< orphan*/ *,struct rpc_msg*) ; 
 scalar_t__ xdr_rmtcall_result ; 
 scalar_t__ xdr_void ; 
 int /*<<< orphan*/  xdrmem_create (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xprt_set_caller (int /*<<< orphan*/ *,struct finfo*) ; 

__attribute__((used)) static void
handle_reply(int fd, SVCXPRT *xprt)
{
	XDR		reply_xdrs;
	struct rpc_msg	reply_msg;
	struct rpc_err	reply_error;
	char		*buffer;
	struct finfo	*fi;
	int		inlen, pos, len;
	struct r_rmtcall_args a;
	struct sockaddr_storage ss;
	socklen_t fromlen;
#ifdef SVC_RUN_DEBUG
	char *uaddr;
#endif

	buffer = malloc(RPC_BUF_MAX);
	if (buffer == NULL)
		goto done;

	do {
		fromlen = sizeof(ss);
		inlen = recvfrom(fd, buffer, RPC_BUF_MAX, 0,
			    (struct sockaddr *)&ss, &fromlen);
	} while (inlen < 0 && errno == EINTR);
	if (inlen < 0) {
		if (debugging)
			fprintf(stderr,
	"handle_reply:  recvfrom returned %d, errno %d\n", inlen, errno);
		goto done;
	}

	reply_msg.acpted_rply.ar_verf = _null_auth;
	reply_msg.acpted_rply.ar_results.where = 0;
	reply_msg.acpted_rply.ar_results.proc = (xdrproc_t) xdr_void;

	xdrmem_create(&reply_xdrs, buffer, (u_int)inlen, XDR_DECODE);
	if (!xdr_replymsg(&reply_xdrs, &reply_msg)) {
		if (debugging)
			(void) fprintf(stderr,
				"handle_reply:  xdr_replymsg failed\n");
		goto done;
	}
	fi = forward_find(reply_msg.rm_xid);
#ifdef	SVC_RUN_DEBUG
	if (debugging) {
		fprintf(stderr, "handle_reply:  reply xid: %d fi addr: %p\n",
			reply_msg.rm_xid, fi);
	}
#endif
	if (fi == NULL) {
		goto done;
	}
	_seterr_reply(&reply_msg, &reply_error);
	if (reply_error.re_status != RPC_SUCCESS) {
		if (debugging)
			(void) fprintf(stderr, "handle_reply:  %s\n",
				clnt_sperrno(reply_error.re_status));
		send_svcsyserr(xprt, fi);
		goto done;
	}
	pos = XDR_GETPOS(&reply_xdrs);
	len = inlen - pos;
	a.rmt_args.args = &buffer[pos];
	a.rmt_args.arglen = len;
	a.rmt_uaddr = fi->uaddr;
	a.rmt_localvers = fi->versnum;

	xprt_set_caller(xprt, fi);
#ifdef	SVC_RUN_DEBUG
	uaddr =	taddr2uaddr(rpcbind_get_conf("udp"),
				    svc_getrpccaller(xprt));
	if (debugging) {
		fprintf(stderr, "handle_reply:  forwarding address %s to %s\n",
			a.rmt_uaddr, uaddr ? uaddr : "unknown");
	}
	free(uaddr);
#endif
	svc_sendreply(xprt, (xdrproc_t) xdr_rmtcall_result, (char *) &a);
done:
	free(buffer);

	if (reply_msg.rm_xid == 0) {
#ifdef	SVC_RUN_DEBUG
	if (debugging) {
		fprintf(stderr, "handle_reply:  NULL xid on exit!\n");
	}
#endif
	} else
		(void) free_slot_by_xid(reply_msg.rm_xid);
	return;
}