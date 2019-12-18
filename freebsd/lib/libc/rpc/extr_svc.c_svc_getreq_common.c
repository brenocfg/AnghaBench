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
struct TYPE_5__ {char* oa_base; } ;
struct svc_req {char* rq_clntcred; scalar_t__ rq_prog; scalar_t__ rq_vers; TYPE_2__ rq_cred; int /*<<< orphan*/  rq_proc; int /*<<< orphan*/ * rq_xprt; } ;
struct svc_callout {scalar_t__ sc_prog; scalar_t__ sc_vers; int /*<<< orphan*/  (* sc_dispatch ) (struct svc_req*,int /*<<< orphan*/ *) ;struct svc_callout* sc_next; } ;
struct TYPE_4__ {char* oa_base; } ;
struct TYPE_6__ {scalar_t__ cb_prog; scalar_t__ cb_vers; TYPE_2__ cb_cred; int /*<<< orphan*/  cb_proc; TYPE_1__ cb_verf; } ;
struct rpc_msg {TYPE_3__ rm_call; } ;
typedef  scalar_t__ rpcvers_t ;
typedef  enum xprt_stat { ____Placeholder_xprt_stat } xprt_stat ;
typedef  enum auth_stat { ____Placeholder_auth_stat } auth_stat ;
typedef  int /*<<< orphan*/  SVCXPRT ;

/* Variables and functions */
 int AUTH_OK ; 
 int FALSE ; 
 int MAX_AUTH_BYTES ; 
 int RPCSEC_GSS_NODISPATCH ; 
 int /*<<< orphan*/  RQCRED_SIZE ; 
 int /*<<< orphan*/  SVC_DESTROY (int /*<<< orphan*/ *) ; 
 scalar_t__ SVC_RECV (int /*<<< orphan*/ *,struct rpc_msg*) ; 
 int SVC_STAT (int /*<<< orphan*/ *) ; 
 int TRUE ; 
 int XPRT_DIED ; 
 int XPRT_MOREREQS ; 
 int /*<<< orphan*/ ** __svc_xports ; 
 int _authenticate (struct svc_req*,struct rpc_msg*) ; 
 int /*<<< orphan*/  rwlock_rdlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rwlock_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct svc_req*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svc_fd_lock ; 
 struct svc_callout* svc_head ; 
 int /*<<< orphan*/  svcerr_auth (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  svcerr_noprog (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svcerr_progvers (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 

void
svc_getreq_common(int fd)
{
	SVCXPRT *xprt;
	struct svc_req r;
	struct rpc_msg msg;
	int prog_found;
	rpcvers_t low_vers;
	rpcvers_t high_vers;
	enum xprt_stat stat;
	char cred_area[2*MAX_AUTH_BYTES + RQCRED_SIZE];

	msg.rm_call.cb_cred.oa_base = cred_area;
	msg.rm_call.cb_verf.oa_base = &(cred_area[MAX_AUTH_BYTES]);
	r.rq_clntcred = &(cred_area[2*MAX_AUTH_BYTES]);

	rwlock_rdlock(&svc_fd_lock);
	xprt = __svc_xports[fd];
	rwlock_unlock(&svc_fd_lock);
	if (xprt == NULL)
		/* But do we control sock? */
		return;
	/* now receive msgs from xprtprt (support batch calls) */
	do {
		if (SVC_RECV(xprt, &msg)) {

			/* now find the exported program and call it */
			struct svc_callout *s;
			enum auth_stat why;

			r.rq_xprt = xprt;
			r.rq_prog = msg.rm_call.cb_prog;
			r.rq_vers = msg.rm_call.cb_vers;
			r.rq_proc = msg.rm_call.cb_proc;
			r.rq_cred = msg.rm_call.cb_cred;
			/* first authenticate the message */
			if ((why = _authenticate(&r, &msg)) != AUTH_OK) {
				/*
				 * RPCSEC_GSS uses this return code
				 * for requests that form part of its
				 * context establishment protocol and
				 * should not be dispatched to the
				 * application.
				 */
				if (why != RPCSEC_GSS_NODISPATCH)
					svcerr_auth(xprt, why);
				goto call_done;
			}
			/* now match message with a registered service*/
			prog_found = FALSE;
			low_vers = (rpcvers_t) -1L;
			high_vers = (rpcvers_t) 0L;
			for (s = svc_head; s != NULL; s = s->sc_next) {
				if (s->sc_prog == r.rq_prog) {
					if (s->sc_vers == r.rq_vers) {
						(*s->sc_dispatch)(&r, xprt);
						goto call_done;
					}  /* found correct version */
					prog_found = TRUE;
					if (s->sc_vers < low_vers)
						low_vers = s->sc_vers;
					if (s->sc_vers > high_vers)
						high_vers = s->sc_vers;
				}   /* found correct program */
			}
			/*
			 * if we got here, the program or version
			 * is not served ...
			 */
			if (prog_found)
				svcerr_progvers(xprt, low_vers, high_vers);
			else
				svcerr_noprog(xprt);
			/* Fall through to ... */
		}
		/*
		 * Check if the xprt has been disconnected in a
		 * recursive call in the service dispatch routine.
		 * If so, then break.
		 */
		rwlock_rdlock(&svc_fd_lock);
		if (xprt != __svc_xports[fd]) {
			rwlock_unlock(&svc_fd_lock);
			break;
		}
		rwlock_unlock(&svc_fd_lock);
call_done:
		if ((stat = SVC_STAT(xprt)) == XPRT_DIED){
			SVC_DESTROY(xprt);
			break;
		}
	} while (stat == XPRT_MOREREQS);
}