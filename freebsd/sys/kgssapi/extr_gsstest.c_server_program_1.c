#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xdrproc_t ;
struct TYPE_6__ {scalar_t__ oa_flavor; } ;
struct svc_req {int rq_proc; TYPE_1__ rq_cred; } ;
struct TYPE_7__ {int uid; int gid; int gidlen; int* gidlist; } ;
typedef  TYPE_2__ rpc_gss_ucred_t ;
struct TYPE_8__ {int service; char* mechanism; } ;
typedef  TYPE_3__ rpc_gss_rawcred_t ;
typedef  int /*<<< orphan*/  SVCXPRT ;

/* Variables and functions */
 scalar_t__ RPCSEC_GSS ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  rpc_gss_getcred (struct svc_req*,TYPE_3__**,TYPE_2__**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svc_freereq (struct svc_req*) ; 
 int /*<<< orphan*/  svc_getargs (struct svc_req*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  svc_sendreply (struct svc_req*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  svcerr_decode (struct svc_req*) ; 
 int /*<<< orphan*/  svcerr_noproc (struct svc_req*) ; 
 int /*<<< orphan*/  svcerr_systemerr (struct svc_req*) ; 
 int /*<<< orphan*/  svcerr_weakauth (struct svc_req*) ; 
 int /*<<< orphan*/  xdr_int ; 
 int /*<<< orphan*/  xdr_void ; 

__attribute__((used)) static void
server_program_1(struct svc_req *rqstp, register SVCXPRT *transp)
{
	rpc_gss_rawcred_t *rcred;
	rpc_gss_ucred_t *ucred;
	int		i, num;

	if (rqstp->rq_cred.oa_flavor != RPCSEC_GSS) {
		svcerr_weakauth(rqstp);
		return;
	}		
		
	if (!rpc_gss_getcred(rqstp, &rcred, &ucred, NULL)) {
		svcerr_systemerr(rqstp);
		return;
	}

	printf("svc=%d, mech=%s, uid=%d, gid=%d, gids={",
	    rcred->service, rcred->mechanism, ucred->uid, ucred->gid);
	for (i = 0; i < ucred->gidlen; i++) {
		if (i > 0) printf(",");
		printf("%d", ucred->gidlist[i]);
	}
	printf("}\n");

	switch (rqstp->rq_proc) {
	case 0:
		if (!svc_getargs(rqstp, (xdrproc_t) xdr_void, 0)) {
			svcerr_decode(rqstp);
			goto out;
		}
		if (!svc_sendreply(rqstp, (xdrproc_t) xdr_void, 0)) {
			svcerr_systemerr(rqstp);
		}
		goto out;

	case 1:
		if (!svc_getargs(rqstp, (xdrproc_t) xdr_int,
			(char *) &num)) {
			svcerr_decode(rqstp);
			goto out;
		}
		num += 100;
		if (!svc_sendreply(rqstp, (xdrproc_t) xdr_int,
			(char *) &num)) {
			svcerr_systemerr(rqstp);
		}
		goto out;

	default:
		svcerr_noproc(rqstp);
		goto out;
	}

out:
	svc_freereq(rqstp);
	return;
}