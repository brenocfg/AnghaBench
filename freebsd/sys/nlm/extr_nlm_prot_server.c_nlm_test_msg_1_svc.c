#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xdrproc_t ;
struct svc_req {int dummy; } ;
struct nlm_testargs {int /*<<< orphan*/  alock; int /*<<< orphan*/  exclusive; int /*<<< orphan*/  cookie; } ;
struct TYPE_12__ {int /*<<< orphan*/  holder; } ;
struct TYPE_13__ {scalar_t__ stat; TYPE_1__ nlm_testrply_u; } ;
struct TYPE_16__ {TYPE_2__ stat; int /*<<< orphan*/  cookie; } ;
typedef  TYPE_5__ nlm_testres ;
struct TYPE_14__ {int /*<<< orphan*/  holder; } ;
struct TYPE_15__ {TYPE_3__ nlm4_testrply_u; int /*<<< orphan*/  stat; } ;
struct TYPE_17__ {TYPE_4__ stat; int /*<<< orphan*/  cookie; } ;
typedef  TYPE_6__ nlm4_testres ;
struct TYPE_18__ {int /*<<< orphan*/  alock; int /*<<< orphan*/  exclusive; int /*<<< orphan*/  cookie; } ;
typedef  TYPE_7__ nlm4_testargs ;
typedef  int /*<<< orphan*/  bool_t ;
typedef  int /*<<< orphan*/  CLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  CLNT_RELEASE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  nlm_convert_to_nlm4_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nlm_convert_to_nlm_holder (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ nlm_convert_to_nlm_stats (int /*<<< orphan*/ ) ; 
 scalar_t__ nlm_denied ; 
 scalar_t__ nlm_do_test (TYPE_7__*,TYPE_6__*,struct svc_req*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  nlm_test_res_1 (TYPE_5__*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlm_zero_tv ; 
 int /*<<< orphan*/  xdr_free (int /*<<< orphan*/ ,TYPE_5__*) ; 
 scalar_t__ xdr_nlm_testres ; 

bool_t
nlm_test_msg_1_svc(struct nlm_testargs *argp, void *result, struct svc_req *rqstp)
{
	nlm4_testargs args4;
	nlm4_testres res4;
	nlm_testres res;
	CLIENT *rpc;
	char dummy;

	args4.cookie = argp->cookie;
	args4.exclusive = argp->exclusive;
	nlm_convert_to_nlm4_lock(&args4.alock, &argp->alock);

	if (nlm_do_test(&args4, &res4, rqstp, &rpc))
		return (FALSE);

	res.cookie = res4.cookie;
	res.stat.stat = nlm_convert_to_nlm_stats(res4.stat.stat);
	if (res.stat.stat == nlm_denied)
		nlm_convert_to_nlm_holder(
			&res.stat.nlm_testrply_u.holder,
			&res4.stat.nlm4_testrply_u.holder);

	if (rpc) {
		nlm_test_res_1(&res, &dummy, rpc, NULL, nlm_zero_tv);
		CLNT_RELEASE(rpc);
	}
	xdr_free((xdrproc_t) xdr_nlm_testres, &res);

	return (FALSE);
}