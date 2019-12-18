#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  ypbind_binding_port; int /*<<< orphan*/  ypbind_binding_addr; } ;
struct TYPE_7__ {scalar_t__ ypsetdom_vers; int /*<<< orphan*/  ypsetdom_domain; TYPE_2__ ypsetdom_binding; } ;
typedef  TYPE_3__ ypbind_setdom ;
typedef  int /*<<< orphan*/  u_short ;
typedef  int /*<<< orphan*/  u_int32_t ;
struct TYPE_5__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_port; TYPE_1__ sin_addr; int /*<<< orphan*/  sin_family; } ;
typedef  int /*<<< orphan*/  SVCXPRT ;
typedef  int /*<<< orphan*/  CLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  INADDR_LOOPBACK ; 
 scalar_t__ IPPORT_RESERVED ; 
 int /*<<< orphan*/  LOG_WARNING ; 
#define  YPSET_ALL 130 
#define  YPSET_LOCAL 129 
#define  YPSET_NO 128 
 scalar_t__ YPVERS ; 
 int /*<<< orphan*/  bzero (struct sockaddr_in*,int) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpc_received (int /*<<< orphan*/ ,struct sockaddr_in*,int) ; 
 scalar_t__ strchr (int /*<<< orphan*/ ,char) ; 
 struct sockaddr_in* svc_getcaller (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svcerr_noprog (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int ypsetmode ; 

void *
ypbindproc_setdom_2_yp(SVCXPRT *transp, ypbind_setdom *argp, CLIENT *clnt)
{
	struct sockaddr_in *fromsin, bindsin;
	static char		*result = NULL;

	if (strchr(argp->ypsetdom_domain, '/')) {
		syslog(LOG_WARNING, "Domain name '%s' has embedded slash -- \
rejecting.", argp->ypsetdom_domain);
		return(NULL);
	}
	fromsin = svc_getcaller(transp);

	switch (ypsetmode) {
	case YPSET_LOCAL:
		if (fromsin->sin_addr.s_addr != htonl(INADDR_LOOPBACK)) {
			svcerr_noprog(transp);
			return(NULL);
		}
		break;
	case YPSET_ALL:
		break;
	case YPSET_NO:
	default:
		svcerr_noprog(transp);
		return(NULL);
	}

	if (ntohs(fromsin->sin_port) >= IPPORT_RESERVED) {
		svcerr_noprog(transp);
		return(NULL);
	}

	if (argp->ypsetdom_vers != YPVERS) {
		svcerr_noprog(transp);
		return(NULL);
	}

	bzero(&bindsin, sizeof bindsin);
	bindsin.sin_family = AF_INET;
	memcpy(&bindsin.sin_addr.s_addr,
	    &argp->ypsetdom_binding.ypbind_binding_addr,
	    sizeof(u_int32_t));
	memcpy(&bindsin.sin_port,
	    &argp->ypsetdom_binding.ypbind_binding_port,
	    sizeof(u_short));
	rpc_received(argp->ypsetdom_domain, &bindsin, 1);

	return((void *) &result);
}