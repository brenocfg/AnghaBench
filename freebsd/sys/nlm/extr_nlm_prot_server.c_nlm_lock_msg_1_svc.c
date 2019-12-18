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
struct nlm_lockargs {int /*<<< orphan*/  state; int /*<<< orphan*/  reclaim; int /*<<< orphan*/  alock; int /*<<< orphan*/  exclusive; int /*<<< orphan*/  block; int /*<<< orphan*/  cookie; } ;
typedef  int /*<<< orphan*/  nlm_res ;
typedef  int /*<<< orphan*/  nlm4_res ;
struct TYPE_3__ {int /*<<< orphan*/  state; int /*<<< orphan*/  reclaim; int /*<<< orphan*/  alock; int /*<<< orphan*/  exclusive; int /*<<< orphan*/  block; int /*<<< orphan*/  cookie; } ;
typedef  TYPE_1__ nlm4_lockargs ;
typedef  int /*<<< orphan*/  bool_t ;
typedef  int /*<<< orphan*/  CLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  CLNT_RELEASE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  nlm_convert_to_nlm4_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nlm_convert_to_nlm_res (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ nlm_do_lock (TYPE_1__*,int /*<<< orphan*/ *,struct svc_req*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  nlm_lock_res_1 (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlm_zero_tv ; 
 int /*<<< orphan*/  xdr_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ xdr_nlm_res ; 

bool_t
nlm_lock_msg_1_svc(struct nlm_lockargs *argp, void *result, struct svc_req *rqstp)
{
	nlm4_lockargs args4;
	nlm4_res res4;
	nlm_res res;
	CLIENT *rpc;
	char dummy;

	args4.cookie = argp->cookie;
	args4.block = argp->block;
	args4.exclusive = argp->exclusive;
	nlm_convert_to_nlm4_lock(&args4.alock, &argp->alock);
	args4.reclaim = argp->reclaim;
	args4.state = argp->state;

	if (nlm_do_lock(&args4, &res4, rqstp, TRUE, &rpc))
		return (FALSE);

	nlm_convert_to_nlm_res(&res, &res4);

	if (rpc) {
		nlm_lock_res_1(&res, &dummy, rpc, NULL, nlm_zero_tv);
		CLNT_RELEASE(rpc);
	}
	xdr_free((xdrproc_t) xdr_nlm_res, &res);

	return (FALSE);
}