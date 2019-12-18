#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct svc_rpc_gss_cookedcred {struct svc_rpc_gss_client* cc_client; } ;
struct svc_rpc_gss_client {void* cl_cookie; int /*<<< orphan*/  cl_ucred; int /*<<< orphan*/  cl_rawcred; } ;
struct TYPE_2__ {scalar_t__ oa_flavor; } ;
struct svc_req {struct svc_rpc_gss_cookedcred* rq_clntcred; TYPE_1__ rq_cred; } ;
typedef  int /*<<< orphan*/  rpc_gss_ucred_t ;
typedef  int /*<<< orphan*/  rpc_gss_rawcred_t ;
typedef  int /*<<< orphan*/  bool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ RPCSEC_GSS ; 
 int /*<<< orphan*/  TRUE ; 

bool_t
rpc_gss_getcred(struct svc_req *req, rpc_gss_rawcred_t **rcred,
    rpc_gss_ucred_t **ucred, void **cookie)
{
	struct svc_rpc_gss_cookedcred *cc;
	struct svc_rpc_gss_client *client;

	if (req->rq_cred.oa_flavor != RPCSEC_GSS)
		return (FALSE);

	cc = req->rq_clntcred;
	client = cc->cc_client;
	if (rcred)
		*rcred = &client->cl_rawcred;
	if (ucred)
		*ucred = &client->cl_ucred;
	if (cookie)
		*cookie = client->cl_cookie;
	return (TRUE);
}