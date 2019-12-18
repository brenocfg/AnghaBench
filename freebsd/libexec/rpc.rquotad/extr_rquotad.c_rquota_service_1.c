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
struct svc_req {int rq_proc; } ;
typedef  int /*<<< orphan*/  SVCXPRT ;

/* Variables and functions */
#define  NULLPROC 130 
#define  RQUOTAPROC_GETACTIVEQUOTA 129 
#define  RQUOTAPROC_GETQUOTA 128 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 scalar_t__ from_inetd ; 
 int /*<<< orphan*/  sendquota (struct svc_req*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svc_sendreply (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  svcerr_noproc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdr_void ; 

__attribute__((used)) static void
rquota_service_1(struct svc_req *request, SVCXPRT *transp)
{

	switch (request->rq_proc) {
	case NULLPROC:
		(void)svc_sendreply(transp, (xdrproc_t)xdr_void, (char *)NULL);
		break;
	case RQUOTAPROC_GETQUOTA:
	case RQUOTAPROC_GETACTIVEQUOTA:
		sendquota(request, transp);
		break;
	default:
		svcerr_noproc(transp);
		break;
	}
	if (from_inetd)
		exit(0);
}