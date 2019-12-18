#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct timeval {scalar_t__ tv_sec; scalar_t__ tv_usec; } ;
struct rpc_callextra {int /*<<< orphan*/  rc_feedback_arg; int /*<<< orphan*/  (* rc_feedback ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_9__ {int tv_sec; scalar_t__ tv_usec; } ;
struct rc_data {int rc_retries; int /*<<< orphan*/  rc_lock; TYPE_2__* rc_client; TYPE_1__ rc_timeout; int /*<<< orphan*/  rc_err; scalar_t__ rc_intr; scalar_t__ rc_closed; } ;
struct mbuf {int dummy; } ;
typedef  int /*<<< orphan*/  rpcproc_t ;
typedef  enum clnt_stat { ____Placeholder_clnt_stat } clnt_stat ;
struct TYPE_10__ {scalar_t__ cl_private; } ;
typedef  TYPE_2__ CLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  CLNT_ACQUIRE (TYPE_2__*) ; 
 int CLNT_CALL_MBUF (TYPE_2__*,struct rpc_callextra*,int /*<<< orphan*/ ,struct mbuf*,struct mbuf**,struct timeval) ; 
 int /*<<< orphan*/  CLNT_GETERR (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CLNT_RELEASE (TYPE_2__*) ; 
 int EINTR ; 
 int ERESTART ; 
 int /*<<< orphan*/  FEEDBACK_RECONNECT ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PCATCH ; 
 int RPC_CANTRECV ; 
 int RPC_CANTSEND ; 
 int RPC_FAILED ; 
 int RPC_INTR ; 
 int RPC_SUCCESS ; 
 int RPC_SYSTEMERROR ; 
 int RPC_TIMEDOUT ; 
 int clnt_reconnect_connect (TYPE_2__*) ; 
 int /*<<< orphan*/  fake_wchan ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int tsleep (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum clnt_stat
clnt_reconnect_call(
	CLIENT		*cl,		/* client handle */
	struct rpc_callextra *ext,	/* call metadata */
	rpcproc_t	proc,		/* procedure number */
	struct mbuf	*args,		/* pointer to args */
	struct mbuf	**resultsp,	/* pointer to results */
	struct timeval	utimeout)
{
	struct rc_data *rc = (struct rc_data *)cl->cl_private;
	CLIENT *client;
	enum clnt_stat stat;
	int tries, error;

	tries = 0;
	do {
		mtx_lock(&rc->rc_lock);
		if (rc->rc_closed) {
			mtx_unlock(&rc->rc_lock);
			return (RPC_CANTSEND);
		}

		if (!rc->rc_client) {
			mtx_unlock(&rc->rc_lock);
			stat = clnt_reconnect_connect(cl);
			if (stat == RPC_SYSTEMERROR) {
				error = tsleep(&fake_wchan,
				    rc->rc_intr ? PCATCH : 0, "rpccon", hz);
				if (error == EINTR || error == ERESTART)
					return (RPC_INTR);
				tries++;
				if (tries >= rc->rc_retries)
					return (stat);
				continue;
			}
			if (stat != RPC_SUCCESS)
				return (stat);
			mtx_lock(&rc->rc_lock);
		}

		if (!rc->rc_client) {
			mtx_unlock(&rc->rc_lock);
			stat = RPC_FAILED;
			continue;
		}
		CLNT_ACQUIRE(rc->rc_client);
		client = rc->rc_client;
		mtx_unlock(&rc->rc_lock);
		stat = CLNT_CALL_MBUF(client, ext, proc, args,
		    resultsp, utimeout);

		if (stat != RPC_SUCCESS) {
			if (!ext)
				CLNT_GETERR(client, &rc->rc_err);
		}

		if (stat == RPC_TIMEDOUT) {
			/*
			 * Check for async send misfeature for NLM
			 * protocol.
			 */
			if ((rc->rc_timeout.tv_sec == 0
				&& rc->rc_timeout.tv_usec == 0)
			    || (rc->rc_timeout.tv_sec == -1
				&& utimeout.tv_sec == 0
				&& utimeout.tv_usec == 0)) {
				CLNT_RELEASE(client);
				break;
			}
		}

		if (stat == RPC_TIMEDOUT || stat == RPC_CANTSEND
		    || stat == RPC_CANTRECV) {
			tries++;
			if (tries >= rc->rc_retries) {
				CLNT_RELEASE(client);
				break;
			}

			if (ext && ext->rc_feedback)
				ext->rc_feedback(FEEDBACK_RECONNECT, proc,
				    ext->rc_feedback_arg);

			mtx_lock(&rc->rc_lock);
			/*
			 * Make sure that someone else hasn't already
			 * reconnected by checking if rc_client has changed.
			 * If not, we are done with the client and must
			 * do CLNT_RELEASE(client) twice to dispose of it,
			 * because there is both an initial refcnt and one
			 * acquired by CLNT_ACQUIRE() above.
			 */
			if (rc->rc_client == client) {
				rc->rc_client = NULL;
				mtx_unlock(&rc->rc_lock);
				CLNT_RELEASE(client);
			} else {
				mtx_unlock(&rc->rc_lock);
			}
			CLNT_RELEASE(client);
		} else {
			CLNT_RELEASE(client);
			break;
		}
	} while (stat != RPC_SUCCESS);

	KASSERT(stat != RPC_SUCCESS || *resultsp,
	    ("RPC_SUCCESS without reply"));

	return (stat);
}