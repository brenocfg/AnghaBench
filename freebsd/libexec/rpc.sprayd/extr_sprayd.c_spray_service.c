#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xdrproc_t ;
struct timeval {int /*<<< orphan*/  tv_usec; int /*<<< orphan*/  tv_sec; } ;
struct svc_req {int rq_proc; } ;
struct TYPE_4__ {int /*<<< orphan*/  usec; int /*<<< orphan*/  sec; } ;
struct TYPE_5__ {TYPE_1__ clock; int /*<<< orphan*/  counter; } ;
typedef  TYPE_2__ spraycumul ;
typedef  int /*<<< orphan*/  SVCXPRT ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_WARNING ; 
#define  NULLPROC 131 
#define  SPRAYPROC_CLEAR 130 
#define  SPRAYPROC_GET 129 
#define  SPRAYPROC_SPRAY 128 
 int /*<<< orphan*/  gettimeofday (struct timeval*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svc_sendreply (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  svcerr_noproc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svcerr_systemerr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  timersub (struct timeval*,struct timeval*,struct timeval*) ; 
 scalar_t__ xdr_spraycumul ; 
 scalar_t__ xdr_void ; 

__attribute__((used)) static void
spray_service(struct svc_req *rqstp, SVCXPRT *transp)
{
	static spraycumul scum;
	static struct timeval clear, get;

	switch (rqstp->rq_proc) {
	case SPRAYPROC_CLEAR:
		scum.counter = 0;
		(void)gettimeofday(&clear, 0);
		/*FALLTHROUGH*/

	case NULLPROC:
		(void)svc_sendreply(transp, (xdrproc_t)xdr_void, NULL);
		return;

	case SPRAYPROC_SPRAY:
		scum.counter++;
		return;

	case SPRAYPROC_GET:
		(void)gettimeofday(&get, 0);
		timersub(&get, &clear, &get);
		scum.clock.sec = get.tv_sec;
		scum.clock.usec = get.tv_usec;
		break;

	default:
		svcerr_noproc(transp);
		return;
	}

	if (!svc_sendreply(transp, (xdrproc_t)xdr_spraycumul, &scum)) {
		svcerr_systemerr(transp);
		syslog(LOG_WARNING, "bad svc_sendreply");
	}
}