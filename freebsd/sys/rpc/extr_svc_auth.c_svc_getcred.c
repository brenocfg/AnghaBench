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
struct xucred {int /*<<< orphan*/  cr_groups; int /*<<< orphan*/  cr_ngroups; int /*<<< orphan*/  cr_uid; } ;
struct ucred {int /*<<< orphan*/ * cr_prison; int /*<<< orphan*/ * cr_groups; int /*<<< orphan*/  cr_svgid; int /*<<< orphan*/  cr_rgid; int /*<<< orphan*/  cr_svuid; int /*<<< orphan*/  cr_ruid; int /*<<< orphan*/  cr_uid; } ;
struct TYPE_2__ {int oa_flavor; } ;
struct svc_req {scalar_t__ rq_clntcred; TYPE_1__ rq_cred; } ;

/* Variables and functions */
#define  AUTH_UNIX 129 
 int FALSE ; 
#define  RPCSEC_GSS 128 
 int TRUE ; 
 int _svcauth_rpcsec_gss_getcred (struct svc_req*,struct ucred**,int*) ; 
 struct ucred* crget () ; 
 int /*<<< orphan*/  crsetgroups (struct ucred*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prison0 ; 
 int /*<<< orphan*/  prison_hold (int /*<<< orphan*/ *) ; 

int
svc_getcred(struct svc_req *rqst, struct ucred **crp, int *flavorp)
{
	struct ucred *cr = NULL;
	int flavor;
	struct xucred *xcr;

	flavor = rqst->rq_cred.oa_flavor;
	if (flavorp)
		*flavorp = flavor;

	switch (flavor) {
	case AUTH_UNIX:
		xcr = (struct xucred *) rqst->rq_clntcred;
		cr = crget();
		cr->cr_uid = cr->cr_ruid = cr->cr_svuid = xcr->cr_uid;
		crsetgroups(cr, xcr->cr_ngroups, xcr->cr_groups);
		cr->cr_rgid = cr->cr_svgid = cr->cr_groups[0];
		cr->cr_prison = &prison0;
		prison_hold(cr->cr_prison);
		*crp = cr;
		return (TRUE);

	case RPCSEC_GSS:
		if (!_svcauth_rpcsec_gss_getcred)
			return (FALSE);
		return (_svcauth_rpcsec_gss_getcred(rqst, crp, flavorp));

	default:
		return (FALSE);
	}
}