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
typedef  int /*<<< orphan*/  xdrproc_t ;
struct svc_req {int rq_proc; } ;
struct nlm_sm_status {int dummy; } ;
typedef  scalar_t__ caddr_t ;
typedef  scalar_t__ bool_t ;
typedef  int /*<<< orphan*/  argument ;
typedef  int /*<<< orphan*/  SVCXPRT ;

/* Variables and functions */
#define  NLM_SM_NOTIFY 129 
#define  NULLPROC 128 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nlm_sm_notify_0_svc ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ stub1 (char*,void*,struct svc_req*) ; 
 int /*<<< orphan*/  svc_freeargs (struct svc_req*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  svc_freereq (struct svc_req*) ; 
 int /*<<< orphan*/  svc_getargs (struct svc_req*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  svc_sendreply (struct svc_req*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  svcerr_decode (struct svc_req*) ; 
 int /*<<< orphan*/  svcerr_noproc (struct svc_req*) ; 
 int /*<<< orphan*/  svcerr_systemerr (struct svc_req*) ; 
 int /*<<< orphan*/  xdr_nlm_sm_status ; 
 int /*<<< orphan*/  xdr_void ; 

void
nlm_prog_0(struct svc_req *rqstp, SVCXPRT *transp)
{
	union {
		struct nlm_sm_status nlm_sm_notify_0_arg;
	} argument;
	char result;
	bool_t retval;
	xdrproc_t xdr_argument, xdr_result;
	bool_t (*local)(char *, void *, struct svc_req *);

	switch (rqstp->rq_proc) {
	case NULLPROC:
		(void) svc_sendreply(rqstp,
			(xdrproc_t) xdr_void, (char *)NULL);
		svc_freereq(rqstp);
		return;

	case NLM_SM_NOTIFY:
		xdr_argument = (xdrproc_t) xdr_nlm_sm_status;
		xdr_result = (xdrproc_t) xdr_void;
		local = (bool_t (*) (char *,  void *,  struct svc_req *))nlm_sm_notify_0_svc;
		break;

	default:
		svcerr_noproc(rqstp);
		svc_freereq(rqstp);
		return;
	}
	(void) memset((char *)&argument, 0, sizeof (argument));
	if (!svc_getargs(rqstp, xdr_argument, (char *)(caddr_t) &argument)) {
		svcerr_decode(rqstp);
		svc_freereq(rqstp);
		return;
	}
	retval = (bool_t) (*local)((char *)&argument, (void *)&result, rqstp);
	if (retval > 0 && !svc_sendreply(rqstp, xdr_result, (char *)&result)) {
		svcerr_systemerr(rqstp);
	}
	if (!svc_freeargs(rqstp, xdr_argument, (char *)(caddr_t) &argument)) {
		printf("unable to free arguments");
		//exit(1);
	}
	svc_freereq(rqstp);

	return;
}