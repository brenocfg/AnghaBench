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
struct svc_req {int dummy; } ;
typedef  int /*<<< orphan*/  nlm4_testargs ;
typedef  int /*<<< orphan*/  nlm4_res ;
typedef  int /*<<< orphan*/  bool_t ;
typedef  int /*<<< orphan*/  CLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  CLNT_RELEASE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  nlm4_granted_res_4 (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ nlm_do_granted (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct svc_req*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  nlm_zero_tv ; 
 int /*<<< orphan*/  xdr_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ xdr_nlm4_res ; 

bool_t
nlm4_granted_msg_4_svc(nlm4_testargs *argp, void *result, struct svc_req *rqstp)
{
	nlm4_res res4;
	CLIENT *rpc;
	char dummy;

	if (nlm_do_granted(argp, &res4, rqstp, &rpc))
		return (FALSE);
	if (rpc) {
		nlm4_granted_res_4(&res4, &dummy, rpc, NULL, nlm_zero_tv);
		CLNT_RELEASE(rpc);
	}
	xdr_free((xdrproc_t) xdr_nlm4_res, &res4);

	return (FALSE);
}