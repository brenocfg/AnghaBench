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
struct TYPE_9__ {scalar_t__ buf; } ;
struct t_bind {scalar_t__ qlen; TYPE_1__ addr; } ;
struct socket {int dummy; } ;
struct sockaddr_storage {int /*<<< orphan*/  ss_len; int /*<<< orphan*/  ss_family; } ;
struct sockaddr {int dummy; } ;
struct netconfig {char* nc_netid; int /*<<< orphan*/  nc_protofmly; } ;
struct __rpc_sockinfo {int si_socktype; int /*<<< orphan*/  si_alen; int /*<<< orphan*/  si_af; } ;
typedef  scalar_t__ bool_t ;
struct TYPE_10__ {int /*<<< orphan*/ * xp_socket; int /*<<< orphan*/  xp_netid; int /*<<< orphan*/  xp_type; } ;
typedef  TYPE_2__ SVCXPRT ;
typedef  int /*<<< orphan*/  SVCPOOL ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  M_RPC ; 
#define  SOCK_DGRAM 129 
#define  SOCK_STREAM 128 
 scalar_t__ TRUE ; 
 struct socket* __rpc_nconf2socket (struct netconfig const*) ; 
 int /*<<< orphan*/  __rpc_nconf2sockinfo (struct netconfig const*,struct __rpc_sockinfo*) ; 
 int /*<<< orphan*/  __rpc_socket2sockinfo (struct socket*,struct __rpc_sockinfo*) ; 
 int /*<<< orphan*/  __rpc_sockisbound (struct socket*) ; 
 int /*<<< orphan*/  __rpc_socktype2seman (int) ; 
 int /*<<< orphan*/  __svc_vc_setflag (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  _getpeername (int /*<<< orphan*/ ,struct sockaddr*,int*) ; 
 scalar_t__ bindresvport (struct socket*,struct sockaddr*) ; 
 int /*<<< orphan*/  curthread ; 
 int /*<<< orphan*/  fd ; 
 int /*<<< orphan*/  memset (struct sockaddr_storage*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int slen ; 
 scalar_t__ sobind (struct socket*,struct sockaddr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  soclose (struct socket*) ; 
 int /*<<< orphan*/  solisten (struct socket*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strdup (char*,int /*<<< orphan*/ ) ; 
 TYPE_2__* svc_dg_create (int /*<<< orphan*/ *,struct socket*,size_t,size_t) ; 
 TYPE_2__* svc_fd_create (int /*<<< orphan*/ ,size_t,size_t) ; 
 TYPE_2__* svc_vc_create (int /*<<< orphan*/ *,struct socket*,size_t,size_t) ; 
 int /*<<< orphan*/  xprt_unregister (TYPE_2__*) ; 

SVCXPRT *
svc_tli_create(
	SVCPOOL *pool,
	struct socket *so,		/* Connection end point */
	const struct netconfig *nconf,	/* Netconfig struct for nettoken */
	const struct t_bind *bindaddr,	/* Local bind address */
	size_t sendsz,			/* Max sendsize */
	size_t recvsz)			/* Max recvsize */
{
	SVCXPRT *xprt = NULL;		/* service handle */
	bool_t madeso = FALSE;		/* whether so opened here  */
	struct __rpc_sockinfo si;
	struct sockaddr_storage ss;

	if (!so) {
		if (nconf == NULL) {
			printf("svc_tli_create: invalid netconfig\n");
			return (NULL);
		}
		so = __rpc_nconf2socket(nconf);
		if (!so) {
			printf(
			    "svc_tli_create: could not open connection for %s\n",
					nconf->nc_netid);
			return (NULL);
		}
		__rpc_nconf2sockinfo(nconf, &si);
		madeso = TRUE;
	} else {
		/*
		 * It is an open socket. Get the transport info.
		 */
		if (!__rpc_socket2sockinfo(so, &si)) {
			printf(
		"svc_tli_create: could not get transport information\n");
			return (NULL);
		}
	}

	/*
	 * If the socket is unbound, try to bind it.
	 */
	if (madeso || !__rpc_sockisbound(so)) {
		if (bindaddr == NULL) {
			if (bindresvport(so, NULL)) {
				memset(&ss, 0, sizeof ss);
				ss.ss_family = si.si_af;
				ss.ss_len = si.si_alen;
				if (sobind(so, (struct sockaddr *)&ss,
					curthread)) {
					printf(
			"svc_tli_create: could not bind to anonymous port\n");
					goto freedata;
				}
			}
			solisten(so, -1, curthread);
		} else {
			if (bindresvport(so,
				(struct sockaddr *)bindaddr->addr.buf)) {
				printf(
		"svc_tli_create: could not bind to requested address\n");
				goto freedata;
			}
			solisten(so, (int)bindaddr->qlen, curthread);
		}
			
	}
	/*
	 * call transport specific function.
	 */
	switch (si.si_socktype) {
		case SOCK_STREAM:
#if 0
			slen = sizeof ss;
			if (_getpeername(fd, (struct sockaddr *)(void *)&ss, &slen)
			    == 0) {
				/* accepted socket */
				xprt = svc_fd_create(fd, sendsz, recvsz);
			} else
#endif
				xprt = svc_vc_create(pool, so, sendsz, recvsz);
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
			xprt = svc_dg_create(pool, so, sendsz, recvsz);
			break;
		default:
			printf("svc_tli_create: bad service type");
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
		xprt->xp_netid = strdup(nconf->nc_netid, M_RPC);
	}
	return (xprt);

freedata:
	if (madeso)
		(void)soclose(so);
	if (xprt) {
		if (!madeso) /* so that svc_destroy doesnt close fd */
			xprt->xp_socket = NULL;
		xprt_unregister(xprt);
	}
	return (NULL);
}