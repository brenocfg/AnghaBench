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
typedef  int /*<<< orphan*/  xdrproc_t ;
struct timeval {scalar_t__ tv_sec; } ;
struct TYPE_4__ {scalar_t__ oa_flavor; } ;
struct svc_req {TYPE_1__ rq_cred; } ;
struct TYPE_5__ {int rq_bsize; int rq_bhardlimit; int rq_bsoftlimit; int rq_curblocks; scalar_t__ rq_ftimeleft; scalar_t__ rq_btimeleft; int /*<<< orphan*/  rq_curfiles; int /*<<< orphan*/  rq_fsoftlimit; int /*<<< orphan*/  rq_fhardlimit; int /*<<< orphan*/  rq_active; } ;
struct TYPE_6__ {TYPE_2__ gqr_rquota; } ;
struct getquota_rslt {TYPE_3__ getquota_rslt_u; int /*<<< orphan*/  status; } ;
struct ext_getquota_args {int /*<<< orphan*/  gqa_pathp; int /*<<< orphan*/  gqa_id; int /*<<< orphan*/  gqa_type; } ;
struct dqblk {int dqb_bhardlimit; int dqb_bsoftlimit; int dqb_curblocks; scalar_t__ dqb_itime; scalar_t__ dqb_btime; int /*<<< orphan*/  dqb_curinodes; int /*<<< orphan*/  dqb_isoftlimit; int /*<<< orphan*/  dqb_ihardlimit; } ;
typedef  int /*<<< orphan*/  getq_args ;
typedef  int /*<<< orphan*/  SVCXPRT ;

/* Variables and functions */
 scalar_t__ AUTH_UNIX ; 
 int DEV_BSIZE ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  Q_EPERM ; 
 int /*<<< orphan*/  Q_NOQUOTA ; 
 int /*<<< orphan*/  Q_OK ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  bzero (struct ext_getquota_args*,int) ; 
 int /*<<< orphan*/  exit (int) ; 
 int flsll (int) ; 
 int /*<<< orphan*/  getfsquota (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dqblk*) ; 
 int /*<<< orphan*/  gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svc_freeargs (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct ext_getquota_args*) ; 
 int /*<<< orphan*/  svc_getargs (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct ext_getquota_args*) ; 
 int /*<<< orphan*/  svc_sendreply (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct getquota_rslt*) ; 
 int /*<<< orphan*/  svcerr_decode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svcerr_systemerr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ xdr_ext_getquota_args ; 
 scalar_t__ xdr_getquota_args ; 
 scalar_t__ xdr_getquota_rslt ; 

__attribute__((used)) static void
sendquota_extended(struct svc_req *request, SVCXPRT *transp)
{
	struct ext_getquota_args getq_args;
	struct getquota_rslt getq_rslt;
	struct dqblk dqblk;
	struct timeval timev;
	int scale;

	bzero(&getq_args, sizeof(getq_args));
	if (!svc_getargs(transp, (xdrproc_t)xdr_ext_getquota_args, &getq_args)) {
		svcerr_decode(transp);
		return;
	}
	if (request->rq_cred.oa_flavor != AUTH_UNIX) {
		/* bad auth */
		getq_rslt.status = Q_EPERM;
	} else if (!getfsquota(getq_args.gqa_type, getq_args.gqa_id, getq_args.gqa_pathp, &dqblk)) {
		/* failed, return noquota */
		getq_rslt.status = Q_NOQUOTA;
	} else {
		gettimeofday(&timev, NULL);
		getq_rslt.status = Q_OK;
		getq_rslt.getquota_rslt_u.gqr_rquota.rq_active = TRUE;
		scale = 1 << flsll(dqblk.dqb_bhardlimit >> 32);
		getq_rslt.getquota_rslt_u.gqr_rquota.rq_bsize =
		    DEV_BSIZE * scale;
		getq_rslt.getquota_rslt_u.gqr_rquota.rq_bhardlimit =
		    dqblk.dqb_bhardlimit / scale;
		getq_rslt.getquota_rslt_u.gqr_rquota.rq_bsoftlimit =
		    dqblk.dqb_bsoftlimit / scale;
		getq_rslt.getquota_rslt_u.gqr_rquota.rq_curblocks =
		    dqblk.dqb_curblocks / scale;
		getq_rslt.getquota_rslt_u.gqr_rquota.rq_fhardlimit =
		    dqblk.dqb_ihardlimit;
		getq_rslt.getquota_rslt_u.gqr_rquota.rq_fsoftlimit =
		    dqblk.dqb_isoftlimit;
		getq_rslt.getquota_rslt_u.gqr_rquota.rq_curfiles =
		    dqblk.dqb_curinodes;
		getq_rslt.getquota_rslt_u.gqr_rquota.rq_btimeleft =
		    dqblk.dqb_btime - timev.tv_sec;
		getq_rslt.getquota_rslt_u.gqr_rquota.rq_ftimeleft =
		    dqblk.dqb_itime - timev.tv_sec;
	}
	if (!svc_sendreply(transp, (xdrproc_t)xdr_getquota_rslt, &getq_rslt))
		svcerr_systemerr(transp);
	if (!svc_freeargs(transp, (xdrproc_t)xdr_getquota_args, &getq_args)) {
		syslog(LOG_ERR, "unable to free arguments");
		exit(1);
	}
}