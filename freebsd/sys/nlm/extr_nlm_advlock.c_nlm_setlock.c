#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xid ;
typedef  int /*<<< orphan*/  xdrproc_t ;
typedef  scalar_t__ u_int ;
struct vnode {int dummy; } ;
struct timeval {int dummy; } ;
struct rpc_callextra {int dummy; } ;
struct nlm_host {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  svid; } ;
struct TYPE_6__ {int stat; } ;
struct TYPE_5__ {int n_len; char* n_bytes; } ;
struct nlm4_res {int block; int exclusive; TYPE_3__ alock; TYPE_2__ stat; TYPE_1__ cookie; int /*<<< orphan*/  state; int /*<<< orphan*/  reclaim; } ;
struct nlm4_lockargs {int block; int exclusive; TYPE_3__ alock; TYPE_2__ stat; TYPE_1__ cookie; int /*<<< orphan*/  state; int /*<<< orphan*/  reclaim; } ;
struct flock {scalar_t__ l_type; } ;
typedef  int /*<<< orphan*/  rpcvers_t ;
typedef  int /*<<< orphan*/  res ;
typedef  int /*<<< orphan*/  off_t ;
typedef  struct nlm4_res nlm4_cancargs ;
typedef  enum clnt_stat { ____Placeholder_clnt_stat } clnt_stat ;
typedef  int /*<<< orphan*/  cancel ;
typedef  int /*<<< orphan*/  bool_t ;
typedef  int /*<<< orphan*/  args ;
typedef  int /*<<< orphan*/  CLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  CLNT_RELEASE (int /*<<< orphan*/ *) ; 
 int EINVAL ; 
 int ENOLCK ; 
 int EWOULDBLOCK ; 
 int FALSE ; 
 int F_WAIT ; 
 scalar_t__ F_WRLCK ; 
 int /*<<< orphan*/  PCATCH ; 
 int RPC_SUCCESS ; 
 int TRUE ; 
 scalar_t__ atomic_fetchadd_int (int /*<<< orphan*/ *,int) ; 
 int hz ; 
 int /*<<< orphan*/  memset (struct nlm4_res*,int /*<<< orphan*/ ,int) ; 
 int nlm4_blocked ; 
#define  nlm4_denied_grace_period 130 
#define  nlm4_granted 129 
 int nlm_cancel_rpc (int /*<<< orphan*/ ,struct nlm4_res*,struct nlm4_res*,int /*<<< orphan*/ *,struct rpc_callextra*,struct timeval) ; 
#define  nlm_denied 128 
 int /*<<< orphan*/  nlm_deregister_wait_lock (void*) ; 
 int /*<<< orphan*/ * nlm_host_get_rpc (struct nlm_host*,int) ; 
 int /*<<< orphan*/  nlm_host_get_sysid (struct nlm_host*) ; 
 int /*<<< orphan*/  nlm_host_monitor (struct nlm_host*,int /*<<< orphan*/ ) ; 
 int nlm_init_lock (struct flock*,int,int,int /*<<< orphan*/ ,size_t,void*,int /*<<< orphan*/ ,TYPE_3__*,char*) ; 
 int nlm_lock_rpc (int /*<<< orphan*/ ,struct nlm4_res*,struct nlm4_res*,int /*<<< orphan*/ *,struct rpc_callextra*,struct timeval) ; 
 int nlm_map_status (int) ; 
 int /*<<< orphan*/  nlm_nsm_state ; 
 int /*<<< orphan*/  nlm_record_lock (struct vnode*,int,struct flock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* nlm_register_wait_lock (TYPE_3__*,struct vnode*) ; 
 int nlm_wait_lock (void*,int) ; 
 int /*<<< orphan*/  nlm_xid ; 
 int /*<<< orphan*/  pause (char*,int) ; 
 int tsleep (struct nlm4_res*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  xdr_free (int /*<<< orphan*/ ,struct nlm4_res*) ; 
 scalar_t__ xdr_nlm4_res ; 

__attribute__((used)) static int
nlm_setlock(struct nlm_host *host, struct rpc_callextra *ext,
    rpcvers_t vers, struct timeval *timo, int retries,
    struct vnode *vp, int op, struct flock *fl, int flags,
    int svid, size_t fhlen, void *fh, off_t size, bool_t reclaim)
{
	struct nlm4_lockargs args;
	char oh_space[32];
	struct nlm4_res res;
	u_int xid;
	CLIENT *client;
	enum clnt_stat stat;
	int retry, block, exclusive;
	void *wait_handle = NULL;
	int error;

	memset(&args, 0, sizeof(args));
	memset(&res, 0, sizeof(res));

	block = (flags & F_WAIT) ? TRUE : FALSE;
	exclusive = (fl->l_type == F_WRLCK);

	error = nlm_init_lock(fl, flags, svid, vers, fhlen, fh, size,
	    &args.alock, oh_space);
	if (error)
		return (error);
	args.block = block;
	args.exclusive = exclusive;
	args.reclaim = reclaim;
	args.state = nlm_nsm_state;

	retry = 5*hz;
	for (;;) {
		client = nlm_host_get_rpc(host, FALSE);
		if (!client)
			return (ENOLCK); /* XXX retry? */

		if (block)
			wait_handle = nlm_register_wait_lock(&args.alock, vp);

		xid = atomic_fetchadd_int(&nlm_xid, 1);
		args.cookie.n_len = sizeof(xid);
		args.cookie.n_bytes = (char*) &xid;

		stat = nlm_lock_rpc(vers, &args, &res, client, ext, *timo);

		CLNT_RELEASE(client);

		if (stat != RPC_SUCCESS) {
			if (block)
				nlm_deregister_wait_lock(wait_handle);
			if (retries) {
				retries--;
				continue;
			}
			return (EINVAL);
		}

		/*
		 * Free res.cookie.
		 */
		xdr_free((xdrproc_t) xdr_nlm4_res, &res);

		if (block && res.stat.stat != nlm4_blocked)
			nlm_deregister_wait_lock(wait_handle);

		if (res.stat.stat == nlm4_denied_grace_period) {
			/*
			 * The server has recently rebooted and is
			 * giving old clients a change to reclaim
			 * their locks. Wait for a few seconds and try
			 * again.
			 */
			error = tsleep(&args, PCATCH, "nlmgrace", retry);
			if (error && error != EWOULDBLOCK)
				return (error);
			retry = 2*retry;
			if (retry > 30*hz)
				retry = 30*hz;
			continue;
		}

		if (block && res.stat.stat == nlm4_blocked) {
			/*
			 * The server should call us back with a
			 * granted message when the lock succeeds. In
			 * order to deal with broken servers, lost
			 * granted messages and server reboots, we
			 * will also re-try every few seconds.
			 */
			error = nlm_wait_lock(wait_handle, retry);
			if (error == EWOULDBLOCK) {
				retry = 2*retry;
				if (retry > 30*hz)
					retry = 30*hz;
				continue;
			}
			if (error) {
				/*
				 * We need to call the server to
				 * cancel our lock request.
				 */
				nlm4_cancargs cancel;

				memset(&cancel, 0, sizeof(cancel));

				xid = atomic_fetchadd_int(&nlm_xid, 1);
				cancel.cookie.n_len = sizeof(xid);
				cancel.cookie.n_bytes = (char*) &xid;
				cancel.block = block;
				cancel.exclusive = exclusive;
				cancel.alock = args.alock;

				do {
					client = nlm_host_get_rpc(host, FALSE);
					if (!client)
						/* XXX retry? */
						return (ENOLCK);

					stat = nlm_cancel_rpc(vers, &cancel,
					    &res, client, ext, *timo);

					CLNT_RELEASE(client);

					if (stat != RPC_SUCCESS) {
						/*
						 * We need to cope
						 * with temporary
						 * network partitions
						 * as well as server
						 * reboots. This means
						 * we have to keep
						 * trying to cancel
						 * until the server
						 * wakes up again.
						 */
						pause("nlmcancel", 10*hz);
					}
				} while (stat != RPC_SUCCESS);

				/*
				 * Free res.cookie.
				 */
				xdr_free((xdrproc_t) xdr_nlm4_res, &res);

				switch (res.stat.stat) {
				case nlm_denied:
					/*
					 * There was nothing
					 * to cancel. We are
					 * going to go ahead
					 * and assume we got
					 * the lock.
					 */
					error = 0;
					break;

				case nlm4_denied_grace_period:
					/*
					 * The server has
					 * recently rebooted -
					 * treat this as a
					 * successful
					 * cancellation.
					 */
					break;

				case nlm4_granted:
					/*
					 * We managed to
					 * cancel.
					 */
					break;

				default:
					/*
					 * Broken server
					 * implementation -
					 * can't really do
					 * anything here.
					 */
					break;
				}

			}
		} else {
			error = nlm_map_status(res.stat.stat);
		}

		if (!error && !reclaim) {
			nlm_record_lock(vp, op, fl, args.alock.svid,
			    nlm_host_get_sysid(host), size);
			nlm_host_monitor(host, 0);
		}

		return (error);
	}
}