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
struct nlm_unlockargs {int dummy; } ;
struct nlm_testargs {int dummy; } ;
struct nlm_lockargs {int dummy; } ;
struct nlm_cancargs {int dummy; } ;
typedef  int /*<<< orphan*/  nlm_testres ;
typedef  int /*<<< orphan*/  nlm_res ;
typedef  scalar_t__ caddr_t ;
typedef  scalar_t__ bool_t ;
typedef  int /*<<< orphan*/  argument ;
typedef  int /*<<< orphan*/  SVCXPRT ;

/* Variables and functions */
#define  NLM_CANCEL 143 
#define  NLM_CANCEL_MSG 142 
#define  NLM_CANCEL_RES 141 
#define  NLM_GRANTED 140 
#define  NLM_GRANTED_MSG 139 
#define  NLM_GRANTED_RES 138 
#define  NLM_LOCK 137 
#define  NLM_LOCK_MSG 136 
#define  NLM_LOCK_RES 135 
#define  NLM_TEST 134 
#define  NLM_TEST_MSG 133 
#define  NLM_TEST_RES 132 
#define  NLM_UNLOCK 131 
#define  NLM_UNLOCK_MSG 130 
#define  NLM_UNLOCK_RES 129 
#define  NULLPROC 128 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nlm_cancel_1_svc ; 
 int /*<<< orphan*/  nlm_cancel_msg_1_svc ; 
 int /*<<< orphan*/  nlm_cancel_res_1_svc ; 
 int /*<<< orphan*/  nlm_granted_1_svc ; 
 int /*<<< orphan*/  nlm_granted_msg_1_svc ; 
 int /*<<< orphan*/  nlm_granted_res_1_svc ; 
 int /*<<< orphan*/  nlm_lock_1_svc ; 
 int /*<<< orphan*/  nlm_lock_msg_1_svc ; 
 int /*<<< orphan*/  nlm_lock_res_1_svc ; 
 int /*<<< orphan*/  nlm_prog_1_freeresult (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  nlm_test_1_svc ; 
 int /*<<< orphan*/  nlm_test_msg_1_svc ; 
 int /*<<< orphan*/  nlm_test_res_1_svc ; 
 int /*<<< orphan*/  nlm_unlock_1_svc ; 
 int /*<<< orphan*/  nlm_unlock_msg_1_svc ; 
 int /*<<< orphan*/  nlm_unlock_res_1_svc ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ stub1 (char*,void*,struct svc_req*) ; 
 int /*<<< orphan*/  svc_freeargs (struct svc_req*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  svc_freereq (struct svc_req*) ; 
 int /*<<< orphan*/  svc_getargs (struct svc_req*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  svc_sendreply (struct svc_req*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  svcerr_decode (struct svc_req*) ; 
 int /*<<< orphan*/  svcerr_noproc (struct svc_req*) ; 
 int /*<<< orphan*/  svcerr_systemerr (struct svc_req*) ; 
 int /*<<< orphan*/  xdr_nlm_cancargs ; 
 int /*<<< orphan*/  xdr_nlm_lockargs ; 
 int /*<<< orphan*/  xdr_nlm_res ; 
 int /*<<< orphan*/  xdr_nlm_testargs ; 
 int /*<<< orphan*/  xdr_nlm_testres ; 
 int /*<<< orphan*/  xdr_nlm_unlockargs ; 
 int /*<<< orphan*/  xdr_void ; 

void
nlm_prog_1(struct svc_req *rqstp, SVCXPRT *transp)
{
	union {
		struct nlm_testargs nlm_test_1_arg;
		struct nlm_lockargs nlm_lock_1_arg;
		struct nlm_cancargs nlm_cancel_1_arg;
		struct nlm_unlockargs nlm_unlock_1_arg;
		struct nlm_testargs nlm_granted_1_arg;
		struct nlm_testargs nlm_test_msg_1_arg;
		struct nlm_lockargs nlm_lock_msg_1_arg;
		struct nlm_cancargs nlm_cancel_msg_1_arg;
		struct nlm_unlockargs nlm_unlock_msg_1_arg;
		struct nlm_testargs nlm_granted_msg_1_arg;
		nlm_testres nlm_test_res_1_arg;
		nlm_res nlm_lock_res_1_arg;
		nlm_res nlm_cancel_res_1_arg;
		nlm_res nlm_unlock_res_1_arg;
		nlm_res nlm_granted_res_1_arg;
	} argument;
	union {
		nlm_testres nlm_test_1_res;
		nlm_res nlm_lock_1_res;
		nlm_res nlm_cancel_1_res;
		nlm_res nlm_unlock_1_res;
		nlm_res nlm_granted_1_res;
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

	case NLM_TEST:
		xdr_argument = (xdrproc_t) xdr_nlm_testargs;
		xdr_result = (xdrproc_t) xdr_nlm_testres;
		local = (bool_t (*) (char *,  void *,  struct svc_req *))nlm_test_1_svc;
		break;

	case NLM_LOCK:
		xdr_argument = (xdrproc_t) xdr_nlm_lockargs;
		xdr_result = (xdrproc_t) xdr_nlm_res;
		local = (bool_t (*) (char *,  void *,  struct svc_req *))nlm_lock_1_svc;
		break;

	case NLM_CANCEL:
		xdr_argument = (xdrproc_t) xdr_nlm_cancargs;
		xdr_result = (xdrproc_t) xdr_nlm_res;
		local = (bool_t (*) (char *,  void *,  struct svc_req *))nlm_cancel_1_svc;
		break;

	case NLM_UNLOCK:
		xdr_argument = (xdrproc_t) xdr_nlm_unlockargs;
		xdr_result = (xdrproc_t) xdr_nlm_res;
		local = (bool_t (*) (char *,  void *,  struct svc_req *))nlm_unlock_1_svc;
		break;

	case NLM_GRANTED:
		xdr_argument = (xdrproc_t) xdr_nlm_testargs;
		xdr_result = (xdrproc_t) xdr_nlm_res;
		local = (bool_t (*) (char *,  void *,  struct svc_req *))nlm_granted_1_svc;
		break;

	case NLM_TEST_MSG:
		xdr_argument = (xdrproc_t) xdr_nlm_testargs;
		xdr_result = (xdrproc_t) xdr_void;
		local = (bool_t (*) (char *,  void *,  struct svc_req *))nlm_test_msg_1_svc;
		break;

	case NLM_LOCK_MSG:
		xdr_argument = (xdrproc_t) xdr_nlm_lockargs;
		xdr_result = (xdrproc_t) xdr_void;
		local = (bool_t (*) (char *,  void *,  struct svc_req *))nlm_lock_msg_1_svc;
		break;

	case NLM_CANCEL_MSG:
		xdr_argument = (xdrproc_t) xdr_nlm_cancargs;
		xdr_result = (xdrproc_t) xdr_void;
		local = (bool_t (*) (char *,  void *,  struct svc_req *))nlm_cancel_msg_1_svc;
		break;

	case NLM_UNLOCK_MSG:
		xdr_argument = (xdrproc_t) xdr_nlm_unlockargs;
		xdr_result = (xdrproc_t) xdr_void;
		local = (bool_t (*) (char *,  void *,  struct svc_req *))nlm_unlock_msg_1_svc;
		break;

	case NLM_GRANTED_MSG:
		xdr_argument = (xdrproc_t) xdr_nlm_testargs;
		xdr_result = (xdrproc_t) xdr_void;
		local = (bool_t (*) (char *,  void *,  struct svc_req *))nlm_granted_msg_1_svc;
		break;

	case NLM_TEST_RES:
		xdr_argument = (xdrproc_t) xdr_nlm_testres;
		xdr_result = (xdrproc_t) xdr_void;
		local = (bool_t (*) (char *,  void *,  struct svc_req *))nlm_test_res_1_svc;
		break;

	case NLM_LOCK_RES:
		xdr_argument = (xdrproc_t) xdr_nlm_res;
		xdr_result = (xdrproc_t) xdr_void;
		local = (bool_t (*) (char *,  void *,  struct svc_req *))nlm_lock_res_1_svc;
		break;

	case NLM_CANCEL_RES:
		xdr_argument = (xdrproc_t) xdr_nlm_res;
		xdr_result = (xdrproc_t) xdr_void;
		local = (bool_t (*) (char *,  void *,  struct svc_req *))nlm_cancel_res_1_svc;
		break;

	case NLM_UNLOCK_RES:
		xdr_argument = (xdrproc_t) xdr_nlm_res;
		xdr_result = (xdrproc_t) xdr_void;
		local = (bool_t (*) (char *,  void *,  struct svc_req *))nlm_unlock_res_1_svc;
		break;

	case NLM_GRANTED_RES:
		xdr_argument = (xdrproc_t) xdr_nlm_res;
		xdr_result = (xdrproc_t) xdr_void;
		local = (bool_t (*) (char *,  void *,  struct svc_req *))nlm_granted_res_1_svc;
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
	if (!nlm_prog_1_freeresult(transp, xdr_result, (caddr_t) &result))
		printf("unable to free results");

	return;
}