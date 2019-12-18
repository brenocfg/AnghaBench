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
struct TYPE_4__ {int oa_flavor; } ;
struct TYPE_6__ {int /*<<< orphan*/ * svc_ah_private; int /*<<< orphan*/ * svc_ah_ops; } ;
struct svc_req {TYPE_1__ rq_cred; TYPE_3__ rq_auth; } ;
struct TYPE_5__ {TYPE_1__ cb_cred; } ;
struct rpc_msg {TYPE_2__ rm_call; } ;
typedef  enum auth_stat { ____Placeholder_auth_stat } auth_stat ;

/* Variables and functions */
#define  AUTH_NULL 131 
 int AUTH_REJECTEDCRED ; 
#define  AUTH_SHORT 130 
#define  AUTH_SYS 129 
#define  RPCSEC_GSS 128 
 int _svcauth_null (struct svc_req*,struct rpc_msg*) ; 
 int _svcauth_rpcsec_gss (struct svc_req*,struct rpc_msg*) ; 
 int _svcauth_short (struct svc_req*,struct rpc_msg*) ; 
 int _svcauth_unix (struct svc_req*,struct rpc_msg*) ; 
 int /*<<< orphan*/  svc_auth_null_ops ; 

enum auth_stat
_authenticate(struct svc_req *rqst, struct rpc_msg *msg)
{
	int cred_flavor;
	enum auth_stat dummy;

	rqst->rq_cred = msg->rm_call.cb_cred;
	rqst->rq_auth.svc_ah_ops = &svc_auth_null_ops;
	rqst->rq_auth.svc_ah_private = NULL;
	cred_flavor = rqst->rq_cred.oa_flavor;
	switch (cred_flavor) {
	case AUTH_NULL:
		dummy = _svcauth_null(rqst, msg);
		return (dummy);
	case AUTH_SYS:
		dummy = _svcauth_unix(rqst, msg);
		return (dummy);
	case AUTH_SHORT:
		dummy = _svcauth_short(rqst, msg);
		return (dummy);
	case RPCSEC_GSS:
		if (!_svcauth_rpcsec_gss)
			return (AUTH_REJECTEDCRED);
		dummy = _svcauth_rpcsec_gss(rqst, msg);
		return (dummy);
	default:
		break;
	}

	return (AUTH_REJECTEDCRED);
}