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
struct sockaddr {scalar_t__ sa_family; } ;
struct request_info {int dummy; } ;
struct pmap {int /*<<< orphan*/  pm_prog; } ;
struct netbuf {scalar_t__ buf; } ;
typedef  int /*<<< orphan*/  rpcprog_t ;
typedef  int const rpcproc_t ;
struct TYPE_2__ {int /*<<< orphan*/  r_prog; } ;
typedef  TYPE_1__ rpcb ;
typedef  int /*<<< orphan*/  SVCXPRT ;

/* Variables and functions */
 scalar_t__ AF_LOCAL ; 
 unsigned int PMAPVERS ; 
#define  RPCBPROC_CALLIT 139 
#define  RPCBPROC_DUMP 138 
#define  RPCBPROC_GETADDR 137 
#define  RPCBPROC_GETADDRLIST 136 
#define  RPCBPROC_GETSTAT 135 
#define  RPCBPROC_GETTIME 134 
#define  RPCBPROC_GETVERSADDR 133 
#define  RPCBPROC_INDIRECT 132 
#define  RPCBPROC_SET 131 
#define  RPCBPROC_TADDR2UADDR 130 
#define  RPCBPROC_UADDR2TADDR 129 
#define  RPCBPROC_UNSET 128 
 int /*<<< orphan*/  RQ_CLIENT_SIN ; 
 int /*<<< orphan*/  RQ_DAEMON ; 
 int /*<<< orphan*/  deny_severity ; 
 int /*<<< orphan*/  hosts_access (struct request_info*) ; 
 int /*<<< orphan*/  insecure ; 
 int /*<<< orphan*/  is_loopback (struct netbuf*) ; 
 scalar_t__ libwrap ; 
 int /*<<< orphan*/  log_severity ; 
 int /*<<< orphan*/  logit (int /*<<< orphan*/ ,struct sockaddr*,int const,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  request_init (struct request_info*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,struct sockaddr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_methods (struct request_info*) ; 
 struct netbuf* svc_getrpccaller (int /*<<< orphan*/ *) ; 
 scalar_t__ verboselog ; 

int 
check_access(SVCXPRT *xprt, rpcproc_t proc, void *args, unsigned int rpcbvers)
{
	struct netbuf *caller = svc_getrpccaller(xprt);
	struct sockaddr *addr = (struct sockaddr *)caller->buf;
#ifdef LIBWRAP
	struct request_info req;
#endif
	rpcprog_t prog = 0;
	rpcb *rpcbp;
	struct pmap *pmap;

	/*
	 * The older PMAP_* equivalents have the same numbers, so
	 * they are accounted for here as well.
	 */
	switch (proc) {
	case RPCBPROC_GETADDR:
	case RPCBPROC_SET:
	case RPCBPROC_UNSET:
		if (rpcbvers > PMAPVERS) {
			rpcbp = (rpcb *)args;
			prog = rpcbp->r_prog;
		} else {
			pmap = (struct pmap *)args;
			prog = pmap->pm_prog;
		}
		if (proc == RPCBPROC_GETADDR)
			break;
		if (!insecure && !is_loopback(caller)) {
			if (verboselog)
				logit(log_severity, addr, proc, prog,
				    " declined (non-loopback sender)");
			return 0;
		}
		break;
	case RPCBPROC_CALLIT:
	case RPCBPROC_INDIRECT:
	case RPCBPROC_DUMP:
	case RPCBPROC_GETTIME:
	case RPCBPROC_UADDR2TADDR:
	case RPCBPROC_TADDR2UADDR:
	case RPCBPROC_GETVERSADDR:
	case RPCBPROC_GETADDRLIST:
	case RPCBPROC_GETSTAT:
	default:
		break;
	}

#ifdef LIBWRAP
	if (libwrap && addr->sa_family != AF_LOCAL) {
		request_init(&req, RQ_DAEMON, "rpcbind", RQ_CLIENT_SIN, addr,
		    0);
		sock_methods(&req);
		if(!hosts_access(&req)) {
			logit(deny_severity, addr, proc, prog,
			    ": request from unauthorized host");
			return 0;
		}
	}
#endif
	if (verboselog)
		logit(log_severity, addr, proc, prog, "");
    	return 1;
}