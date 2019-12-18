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
typedef  int /*<<< orphan*/  nlm4_unlockargs ;
typedef  int /*<<< orphan*/  nlm4_testres ;
typedef  int /*<<< orphan*/  nlm4_testargs ;
typedef  int /*<<< orphan*/  nlm4_shareres ;
typedef  int /*<<< orphan*/  nlm4_shareargs ;
typedef  int /*<<< orphan*/  nlm4_res ;
typedef  int /*<<< orphan*/  nlm4_notify ;
typedef  int /*<<< orphan*/  nlm4_lockargs ;
typedef  int /*<<< orphan*/  nlm4_cancargs ;
typedef  scalar_t__ caddr_t ;
typedef  scalar_t__ bool_t ;
typedef  int /*<<< orphan*/  argument ;
typedef  int /*<<< orphan*/  SVCXPRT ;

/* Variables and functions */
#define  NLM4_CANCEL 147 
#define  NLM4_CANCEL_MSG 146 
#define  NLM4_CANCEL_RES 145 
#define  NLM4_FREE_ALL 144 
#define  NLM4_GRANTED 143 
#define  NLM4_GRANTED_MSG 142 
#define  NLM4_GRANTED_RES 141 
#define  NLM4_LOCK 140 
#define  NLM4_LOCK_MSG 139 
#define  NLM4_LOCK_RES 138 
#define  NLM4_NM_LOCK 137 
#define  NLM4_SHARE 136 
#define  NLM4_TEST 135 
#define  NLM4_TEST_MSG 134 
#define  NLM4_TEST_RES 133 
#define  NLM4_UNLOCK 132 
#define  NLM4_UNLOCK_MSG 131 
#define  NLM4_UNLOCK_RES 130 
#define  NLM4_UNSHARE 129 
#define  NULLPROC 128 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nlm4_cancel_4_svc ; 
 int /*<<< orphan*/  nlm4_cancel_msg_4_svc ; 
 int /*<<< orphan*/  nlm4_cancel_res_4_svc ; 
 int /*<<< orphan*/  nlm4_free_all_4_svc ; 
 int /*<<< orphan*/  nlm4_granted_4_svc ; 
 int /*<<< orphan*/  nlm4_granted_msg_4_svc ; 
 int /*<<< orphan*/  nlm4_granted_res_4_svc ; 
 int /*<<< orphan*/  nlm4_lock_4_svc ; 
 int /*<<< orphan*/  nlm4_lock_msg_4_svc ; 
 int /*<<< orphan*/  nlm4_lock_res_4_svc ; 
 int /*<<< orphan*/  nlm4_nm_lock_4_svc ; 
 int /*<<< orphan*/  nlm4_share_4_svc ; 
 int /*<<< orphan*/  nlm4_test_4_svc ; 
 int /*<<< orphan*/  nlm4_test_msg_4_svc ; 
 int /*<<< orphan*/  nlm4_test_res_4_svc ; 
 int /*<<< orphan*/  nlm4_unlock_4_svc ; 
 int /*<<< orphan*/  nlm4_unlock_msg_4_svc ; 
 int /*<<< orphan*/  nlm4_unlock_res_4_svc ; 
 int /*<<< orphan*/  nlm4_unshare_4_svc ; 
 int /*<<< orphan*/  nlm_prog_4_freeresult (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ stub1 (char*,void*,struct svc_req*) ; 
 int /*<<< orphan*/  svc_freeargs (struct svc_req*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  svc_freereq (struct svc_req*) ; 
 int /*<<< orphan*/  svc_getargs (struct svc_req*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  svc_sendreply (struct svc_req*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  svcerr_decode (struct svc_req*) ; 
 int /*<<< orphan*/  svcerr_noproc (struct svc_req*) ; 
 int /*<<< orphan*/  svcerr_systemerr (struct svc_req*) ; 
 int /*<<< orphan*/  xdr_nlm4_cancargs ; 
 int /*<<< orphan*/  xdr_nlm4_lockargs ; 
 int /*<<< orphan*/  xdr_nlm4_notify ; 
 int /*<<< orphan*/  xdr_nlm4_res ; 
 int /*<<< orphan*/  xdr_nlm4_shareargs ; 
 int /*<<< orphan*/  xdr_nlm4_shareres ; 
 int /*<<< orphan*/  xdr_nlm4_testargs ; 
 int /*<<< orphan*/  xdr_nlm4_testres ; 
 int /*<<< orphan*/  xdr_nlm4_unlockargs ; 
 int /*<<< orphan*/  xdr_void ; 

void
nlm_prog_4(struct svc_req *rqstp, SVCXPRT *transp)
{
	union {
		nlm4_testargs nlm4_test_4_arg;
		nlm4_lockargs nlm4_lock_4_arg;
		nlm4_cancargs nlm4_cancel_4_arg;
		nlm4_unlockargs nlm4_unlock_4_arg;
		nlm4_testargs nlm4_granted_4_arg;
		nlm4_testargs nlm4_test_msg_4_arg;
		nlm4_lockargs nlm4_lock_msg_4_arg;
		nlm4_cancargs nlm4_cancel_msg_4_arg;
		nlm4_unlockargs nlm4_unlock_msg_4_arg;
		nlm4_testargs nlm4_granted_msg_4_arg;
		nlm4_testres nlm4_test_res_4_arg;
		nlm4_res nlm4_lock_res_4_arg;
		nlm4_res nlm4_cancel_res_4_arg;
		nlm4_res nlm4_unlock_res_4_arg;
		nlm4_res nlm4_granted_res_4_arg;
		nlm4_shareargs nlm4_share_4_arg;
		nlm4_shareargs nlm4_unshare_4_arg;
		nlm4_lockargs nlm4_nm_lock_4_arg;
		nlm4_notify nlm4_free_all_4_arg;
	} argument;
	union {
		nlm4_testres nlm4_test_4_res;
		nlm4_res nlm4_lock_4_res;
		nlm4_res nlm4_cancel_4_res;
		nlm4_res nlm4_unlock_4_res;
		nlm4_res nlm4_granted_4_res;
		nlm4_shareres nlm4_share_4_res;
		nlm4_shareres nlm4_unshare_4_res;
		nlm4_res nlm4_nm_lock_4_res;
	} result;
	bool_t retval;
	xdrproc_t xdr_argument, xdr_result;
	bool_t (*local)(char *, void *, struct svc_req *);

	switch (rqstp->rq_proc) {
	case NULLPROC:
		(void) svc_sendreply(rqstp,
			(xdrproc_t) xdr_void, (char *)NULL);
		svc_freereq(rqstp);
		return;

	case NLM4_TEST:
		xdr_argument = (xdrproc_t) xdr_nlm4_testargs;
		xdr_result = (xdrproc_t) xdr_nlm4_testres;
		local = (bool_t (*) (char *,  void *,  struct svc_req *))nlm4_test_4_svc;
		break;

	case NLM4_LOCK:
		xdr_argument = (xdrproc_t) xdr_nlm4_lockargs;
		xdr_result = (xdrproc_t) xdr_nlm4_res;
		local = (bool_t (*) (char *,  void *,  struct svc_req *))nlm4_lock_4_svc;
		break;

	case NLM4_CANCEL:
		xdr_argument = (xdrproc_t) xdr_nlm4_cancargs;
		xdr_result = (xdrproc_t) xdr_nlm4_res;
		local = (bool_t (*) (char *,  void *,  struct svc_req *))nlm4_cancel_4_svc;
		break;

	case NLM4_UNLOCK:
		xdr_argument = (xdrproc_t) xdr_nlm4_unlockargs;
		xdr_result = (xdrproc_t) xdr_nlm4_res;
		local = (bool_t (*) (char *,  void *,  struct svc_req *))nlm4_unlock_4_svc;
		break;

	case NLM4_GRANTED:
		xdr_argument = (xdrproc_t) xdr_nlm4_testargs;
		xdr_result = (xdrproc_t) xdr_nlm4_res;
		local = (bool_t (*) (char *,  void *,  struct svc_req *))nlm4_granted_4_svc;
		break;

	case NLM4_TEST_MSG:
		xdr_argument = (xdrproc_t) xdr_nlm4_testargs;
		xdr_result = (xdrproc_t) xdr_void;
		local = (bool_t (*) (char *,  void *,  struct svc_req *))nlm4_test_msg_4_svc;
		break;

	case NLM4_LOCK_MSG:
		xdr_argument = (xdrproc_t) xdr_nlm4_lockargs;
		xdr_result = (xdrproc_t) xdr_void;
		local = (bool_t (*) (char *,  void *,  struct svc_req *))nlm4_lock_msg_4_svc;
		break;

	case NLM4_CANCEL_MSG:
		xdr_argument = (xdrproc_t) xdr_nlm4_cancargs;
		xdr_result = (xdrproc_t) xdr_void;
		local = (bool_t (*) (char *,  void *,  struct svc_req *))nlm4_cancel_msg_4_svc;
		break;

	case NLM4_UNLOCK_MSG:
		xdr_argument = (xdrproc_t) xdr_nlm4_unlockargs;
		xdr_result = (xdrproc_t) xdr_void;
		local = (bool_t (*) (char *,  void *,  struct svc_req *))nlm4_unlock_msg_4_svc;
		break;

	case NLM4_GRANTED_MSG:
		xdr_argument = (xdrproc_t) xdr_nlm4_testargs;
		xdr_result = (xdrproc_t) xdr_void;
		local = (bool_t (*) (char *,  void *,  struct svc_req *))nlm4_granted_msg_4_svc;
		break;

	case NLM4_TEST_RES:
		xdr_argument = (xdrproc_t) xdr_nlm4_testres;
		xdr_result = (xdrproc_t) xdr_void;
		local = (bool_t (*) (char *,  void *,  struct svc_req *))nlm4_test_res_4_svc;
		break;

	case NLM4_LOCK_RES:
		xdr_argument = (xdrproc_t) xdr_nlm4_res;
		xdr_result = (xdrproc_t) xdr_void;
		local = (bool_t (*) (char *,  void *,  struct svc_req *))nlm4_lock_res_4_svc;
		break;

	case NLM4_CANCEL_RES:
		xdr_argument = (xdrproc_t) xdr_nlm4_res;
		xdr_result = (xdrproc_t) xdr_void;
		local = (bool_t (*) (char *,  void *,  struct svc_req *))nlm4_cancel_res_4_svc;
		break;

	case NLM4_UNLOCK_RES:
		xdr_argument = (xdrproc_t) xdr_nlm4_res;
		xdr_result = (xdrproc_t) xdr_void;
		local = (bool_t (*) (char *,  void *,  struct svc_req *))nlm4_unlock_res_4_svc;
		break;

	case NLM4_GRANTED_RES:
		xdr_argument = (xdrproc_t) xdr_nlm4_res;
		xdr_result = (xdrproc_t) xdr_void;
		local = (bool_t (*) (char *,  void *,  struct svc_req *))nlm4_granted_res_4_svc;
		break;

	case NLM4_SHARE:
		xdr_argument = (xdrproc_t) xdr_nlm4_shareargs;
		xdr_result = (xdrproc_t) xdr_nlm4_shareres;
		local = (bool_t (*) (char *,  void *,  struct svc_req *))nlm4_share_4_svc;
		break;

	case NLM4_UNSHARE:
		xdr_argument = (xdrproc_t) xdr_nlm4_shareargs;
		xdr_result = (xdrproc_t) xdr_nlm4_shareres;
		local = (bool_t (*) (char *,  void *,  struct svc_req *))nlm4_unshare_4_svc;
		break;

	case NLM4_NM_LOCK:
		xdr_argument = (xdrproc_t) xdr_nlm4_lockargs;
		xdr_result = (xdrproc_t) xdr_nlm4_res;
		local = (bool_t (*) (char *,  void *,  struct svc_req *))nlm4_nm_lock_4_svc;
		break;

	case NLM4_FREE_ALL:
		xdr_argument = (xdrproc_t) xdr_nlm4_notify;
		xdr_result = (xdrproc_t) xdr_void;
		local = (bool_t (*) (char *,  void *,  struct svc_req *))nlm4_free_all_4_svc;
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
	if (!nlm_prog_4_freeresult(transp, xdr_result, (caddr_t) &result))
		printf("unable to free results");

	return;
}