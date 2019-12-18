#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xdrproc_t ;
struct svc_req {int dummy; } ;
struct nlm_testargs {int /*<<< orphan*/  alock; int /*<<< orphan*/  exclusive; int /*<<< orphan*/  cookie; } ;
typedef  int /*<<< orphan*/  nlm_res ;
struct TYPE_3__ {int /*<<< orphan*/  alock; int /*<<< orphan*/  exclusive; int /*<<< orphan*/  cookie; } ;
typedef  TYPE_1__ nlm4_testargs ;
typedef  int /*<<< orphan*/  nlm4_res ;
typedef  int /*<<< orphan*/  bool_t ;
typedef  int /*<<< orphan*/  CLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  CLNT_RELEASE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  nlm_convert_to_nlm4_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nlm_convert_to_nlm_res (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ nlm_do_granted (TYPE_1__*,int /*<<< orphan*/ *,struct svc_req*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  nlm_granted_res_1 (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlm_zero_tv ; 
 int /*<<< orphan*/  xdr_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ xdr_nlm_res ; 

bool_t
nlm_granted_msg_1_svc(struct nlm_testargs *argp, void *result, struct svc_req *rqstp)
{
	nlm4_testargs args4;
	nlm4_res res4;
	nlm_res res;
	CLIENT *rpc;
	char dummy;

	args4.cookie = argp->cookie;
	args4.exclusive = argp->exclusive;
	nlm_convert_to_nlm4_lock(&args4.alock, &argp->alock);

	if (nlm_do_granted(&args4, &res4, rqstp, &rpc))
		return (FALSE);

	nlm_convert_to_nlm_res(&res, &res4);

	if (rpc) {
		nlm_granted_res_1(&res, &dummy, rpc, NULL, nlm_zero_tv);
		CLNT_RELEASE(rpc);
	}
	xdr_free((xdrproc_t) xdr_nlm_res, &res);

	return (FALSE);
}