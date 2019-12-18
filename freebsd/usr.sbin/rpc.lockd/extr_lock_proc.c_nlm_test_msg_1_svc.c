#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xdrproc_t ;
struct timeval {scalar_t__ tv_usec; scalar_t__ tv_sec; } ;
struct svc_req {int /*<<< orphan*/  rq_xprt; } ;
struct sockaddr {int dummy; } ;
struct nlm_holder {int dummy; } ;
struct nlm4_lock {int dummy; } ;
struct nlm4_holder {int /*<<< orphan*/  l_len; int /*<<< orphan*/  l_offset; } ;
struct TYPE_14__ {int /*<<< orphan*/  l_len; int /*<<< orphan*/  l_offset; } ;
struct TYPE_9__ {TYPE_7__ holder; } ;
struct TYPE_10__ {TYPE_1__ nlm_testrply_u; int /*<<< orphan*/  stat; } ;
struct TYPE_11__ {TYPE_2__ stat; int /*<<< orphan*/  cookie; } ;
typedef  TYPE_3__ nlm_testres ;
struct TYPE_12__ {int /*<<< orphan*/  cookie; int /*<<< orphan*/  exclusive; int /*<<< orphan*/  alock; } ;
typedef  TYPE_4__ nlm_testargs ;
struct TYPE_13__ {struct sockaddr* buf; } ;
typedef  int /*<<< orphan*/  CLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  NLM_TEST_RES ; 
 int /*<<< orphan*/  NLM_VERS ; 
 int clnt_call (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ,char*,struct timeval) ; 
 int debug_level ; 
 int /*<<< orphan*/ * get_client (struct sockaddr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_from_addr (char*,struct svc_req*) ; 
 int /*<<< orphan*/  memcpy (TYPE_7__*,struct nlm4_holder*,int) ; 
 int /*<<< orphan*/  nlm_denied ; 
 int /*<<< orphan*/  nlm_granted ; 
 int /*<<< orphan*/  nlmtonlm4 (int /*<<< orphan*/ *,struct nlm4_lock*) ; 
 TYPE_5__* svc_getrpccaller (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,int) ; 
 struct nlm4_holder* testlock (struct nlm4_lock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ xdr_nlm_testres ; 
 scalar_t__ xdr_void ; 

void *
nlm_test_msg_1_svc(nlm_testargs *arg, struct svc_req *rqstp)
{
	nlm_testres res;
	static char dummy;
	struct sockaddr *addr;
	CLIENT *cli;
	int success;
	struct timeval timeo;
	struct nlm4_lock arg4;
	struct nlm4_holder *holder;

	nlmtonlm4(&arg->alock, &arg4);

	if (debug_level)
		log_from_addr("nlm_test_msg", rqstp);

	holder = testlock(&arg4, arg->exclusive, 0);

	res.cookie = arg->cookie;
	if (holder == NULL) {
		res.stat.stat = nlm_granted;
	} else {
		res.stat.stat = nlm_denied;
		memcpy(&res.stat.nlm_testrply_u.holder, holder,
		    sizeof(struct nlm_holder));
		res.stat.nlm_testrply_u.holder.l_offset = holder->l_offset;
		res.stat.nlm_testrply_u.holder.l_len = holder->l_len;
	}

	/*
	 * nlm_test has different result type to the other operations, so
	 * can't use transmit_result() in this case
	 */
	addr = svc_getrpccaller(rqstp->rq_xprt)->buf;
	if ((cli = get_client(addr, NLM_VERS)) != NULL) {
		timeo.tv_sec = 0; /* No timeout - not expecting response */
		timeo.tv_usec = 0;

		success = clnt_call(cli, NLM_TEST_RES,
		    (xdrproc_t)xdr_nlm_testres, &res,
		    (xdrproc_t)xdr_void, &dummy, timeo);

		if (debug_level > 2)
			syslog(LOG_DEBUG, "clnt_call returns %d", success);
	}
	return (NULL);
}