#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int ;
struct TYPE_9__ {scalar_t__ buf; } ;
struct t_bind {scalar_t__ qlen; TYPE_1__ addr; } ;
struct sockaddr_storage {scalar_t__ ss_len; int /*<<< orphan*/  ss_family; } ;
struct sockaddr {int dummy; } ;
struct netconfig {int /*<<< orphan*/  nc_device; int /*<<< orphan*/  nc_netid; int /*<<< orphan*/  nc_protofmly; } ;
struct __rpc_sockinfo {int si_socktype; scalar_t__ si_alen; int /*<<< orphan*/  si_af; } ;
typedef  int socklen_t ;
typedef  scalar_t__ bool_t ;
struct TYPE_10__ {int xp_fd; void* xp_tp; void* xp_netid; int /*<<< orphan*/  xp_type; } ;
typedef  TYPE_2__ SVCXPRT ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int RPC_ANYFD ; 
#define  SOCK_DGRAM 129 
#define  SOCK_STREAM 128 
 int SOMAXCONN ; 
 int /*<<< orphan*/  SVC_DESTROY (TYPE_2__*) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  __rpc_fd2sockinfo (int,struct __rpc_sockinfo*) ; 
 int __rpc_nconf2fd (struct netconfig const*) ; 
 int /*<<< orphan*/  __rpc_nconf2sockinfo (struct netconfig const*,struct __rpc_sockinfo*) ; 
 int /*<<< orphan*/  __rpc_sockisbound (int) ; 
 int /*<<< orphan*/  __rpc_socktype2seman (int) ; 
 int /*<<< orphan*/  __svc_vc_setflag (TYPE_2__*,scalar_t__) ; 
 scalar_t__ _bind (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  _close (int) ; 
 int /*<<< orphan*/  _getpeername (int,struct sockaddr*,int*) ; 
 int /*<<< orphan*/  _listen (int,int) ; 
 scalar_t__ bindresvport (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct sockaddr_storage*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 void* strdup (int /*<<< orphan*/ ) ; 
 TYPE_2__* svc_dg_create (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* svc_fd_create (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* svc_vc_create (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warnx (char*,...) ; 

SVCXPRT *
svc_tli_create(int fd, const struct netconfig *nconf,
    const struct t_bind *bindaddr, u_int sendsz, u_int recvsz)
{
	SVCXPRT *xprt = NULL;		/* service handle */
	bool_t madefd = FALSE;		/* whether fd opened here  */
	struct __rpc_sockinfo si;
	struct sockaddr_storage ss;
	socklen_t slen;

	if (fd == RPC_ANYFD) {
		if (nconf == NULL) {
			warnx("svc_tli_create: invalid netconfig");
			return (NULL);
		}
		fd = __rpc_nconf2fd(nconf);
		if (fd == -1) {
			warnx(
			    "svc_tli_create: could not open connection for %s",
					nconf->nc_netid);
			return (NULL);
		}
		__rpc_nconf2sockinfo(nconf, &si);
		madefd = TRUE;
	} else {
		/*
		 * It is an open descriptor. Get the transport info.
		 */
		if (!__rpc_fd2sockinfo(fd, &si)) {
			warnx(
		"svc_tli_create: could not get transport information");
			return (NULL);
		}
	}

	/*
	 * If the fd is unbound, try to bind it.
	 */
	if (madefd || !__rpc_sockisbound(fd)) {
		if (bindaddr == NULL) {
			if (bindresvport(fd, NULL) < 0) {
				memset(&ss, 0, sizeof ss);
				ss.ss_family = si.si_af;
				ss.ss_len = si.si_alen;
				if (_bind(fd, (struct sockaddr *)(void *)&ss,
				    (socklen_t)si.si_alen) < 0) {
					warnx(
			"svc_tli_create: could not bind to anonymous port");
					goto freedata;
				}
			}
			_listen(fd, SOMAXCONN);
		} else {
			if (_bind(fd,
			    (struct sockaddr *)bindaddr->addr.buf,
			    (socklen_t)si.si_alen) < 0) {
				warnx(
		"svc_tli_create: could not bind to requested address");
				goto freedata;
			}
			_listen(fd, (int)bindaddr->qlen);
		}
			
	}
	/*
	 * call transport specific function.
	 */
	switch (si.si_socktype) {
		case SOCK_STREAM:
			slen = sizeof ss;
			if (_getpeername(fd, (struct sockaddr *)(void *)&ss, &slen)
			    == 0) {
				/* accepted socket */
				xprt = svc_fd_create(fd, sendsz, recvsz);
			} else
				xprt = svc_vc_create(fd, sendsz, recvsz);
			if (!nconf || !xprt)
				break;
#if 0
			/* XXX fvdl */
			if (strcmp(nconf->nc_protofmly, "inet") == 0 ||
			    strcmp(nconf->nc_protofmly, "inet6") == 0)
				(void) __svc_vc_setflag(xprt, TRUE);
#endif
			break;
		case SOCK_DGRAM:
			xprt = svc_dg_create(fd, sendsz, recvsz);
			break;
		default:
			warnx("svc_tli_create: bad service type");
			goto freedata;
	}

	if (xprt == NULL)
		/*
		 * The error messages here are spitted out by the lower layers:
		 * svc_vc_create(), svc_fd_create() and svc_dg_create().
		 */
		goto freedata;

	/* Fill in type of service */
	xprt->xp_type = __rpc_socktype2seman(si.si_socktype);

	if (nconf) {
		xprt->xp_netid = strdup(nconf->nc_netid);
		xprt->xp_tp = strdup(nconf->nc_device);
	}
	return (xprt);

freedata:
	if (madefd)
		(void)_close(fd);
	if (xprt) {
		if (!madefd) /* so that svc_destroy doesnt close fd */
			xprt->xp_fd = RPC_ANYFD;
		SVC_DESTROY(xprt);
	}
	return (NULL);
}