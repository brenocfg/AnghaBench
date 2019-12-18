#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ xdrproc_t ;
struct svc_req {scalar_t__ rq_proc; scalar_t__ rq_prog; scalar_t__ rq_vers; } ;
struct proglst {scalar_t__ p_prognum; scalar_t__ p_procnum; scalar_t__ p_versnum; char* p_xdrbuf; char* (* p_progname ) (char*) ;scalar_t__ p_outproc; int /*<<< orphan*/  p_inproc; scalar_t__ p_recvsz; int /*<<< orphan*/  p_netid; struct proglst* p_nxt; } ;
typedef  scalar_t__ rpcvers_t ;
typedef  scalar_t__ rpcprog_t ;
typedef  scalar_t__ rpcproc_t ;
struct TYPE_7__ {int /*<<< orphan*/  xp_netid; } ;
typedef  TYPE_1__ SVCXPRT ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ NULLPROC ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct proglst* proglst ; 
 int /*<<< orphan*/  proglst_lock ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* stub1 (char*) ; 
 int /*<<< orphan*/  svc_freeargs (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  svc_getargs (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ svc_sendreply (TYPE_1__*,scalar_t__,char*) ; 
 int /*<<< orphan*/  svcerr_decode (TYPE_1__*) ; 
 int /*<<< orphan*/  warnx (char*,...) ; 
 scalar_t__ xdr_void ; 

__attribute__((used)) static void
universal(struct svc_req *rqstp, SVCXPRT *transp)
{
	rpcprog_t prog;
	rpcvers_t vers;
	rpcproc_t proc;
	char *outdata;
	char *xdrbuf;
	struct proglst *pl;

	/*
	 * enforce "procnum 0 is echo" convention
	 */
	if (rqstp->rq_proc == NULLPROC) {
		if (svc_sendreply(transp, (xdrproc_t) xdr_void, NULL) ==
		    FALSE) {
			warnx("svc_sendreply failed");
		}
		return;
	}
	prog = rqstp->rq_prog;
	vers = rqstp->rq_vers;
	proc = rqstp->rq_proc;
	mutex_lock(&proglst_lock);
	for (pl = proglst; pl; pl = pl->p_nxt)
		if (pl->p_prognum == prog && pl->p_procnum == proc &&
			pl->p_versnum == vers &&
			(strcmp(pl->p_netid, transp->xp_netid) == 0)) {
			/* decode arguments into a CLEAN buffer */
			xdrbuf = pl->p_xdrbuf;
			/* Zero the arguments: reqd ! */
			(void) memset(xdrbuf, 0, (size_t)pl->p_recvsz);
			/*
			 * Assuming that sizeof (xdrbuf) would be enough
			 * for the arguments; if not then the program
			 * may bomb. BEWARE!
			 */
			if (!svc_getargs(transp, pl->p_inproc, xdrbuf)) {
				svcerr_decode(transp);
				mutex_unlock(&proglst_lock);
				return;
			}
			outdata = (*(pl->p_progname))(xdrbuf);
			if (outdata == NULL &&
				pl->p_outproc != (xdrproc_t) xdr_void){
				/* there was an error */
				mutex_unlock(&proglst_lock);
				return;
			}
			if (!svc_sendreply(transp, pl->p_outproc, outdata)) {
				warnx(
			"rpc: rpc_reg trouble replying to prog %u vers %u",
				(unsigned)prog, (unsigned)vers);
				mutex_unlock(&proglst_lock);
				return;
			}
			/* free the decoded arguments */
			(void)svc_freeargs(transp, pl->p_inproc, xdrbuf);
			mutex_unlock(&proglst_lock);
			return;
		}
	mutex_unlock(&proglst_lock);
	/* This should never happen */
	warnx("rpc: rpc_reg: never registered prog %u vers %u",
		(unsigned)prog, (unsigned)vers);
	return;
}