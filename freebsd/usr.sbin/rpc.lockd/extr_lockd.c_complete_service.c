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
struct netconfig {scalar_t__ nc_semantics; int /*<<< orphan*/  nc_netid; } ;
struct netbuf {int /*<<< orphan*/  len; int /*<<< orphan*/  buf; } ;
struct addrinfo {int /*<<< orphan*/  ai_addrlen; int /*<<< orphan*/  ai_addr; int /*<<< orphan*/  ai_protocol; int /*<<< orphan*/  ai_socktype; int /*<<< orphan*/  ai_family; int /*<<< orphan*/  ai_flags; } ;
struct __rpc_sockinfo {int /*<<< orphan*/  si_proto; int /*<<< orphan*/  si_socktype; int /*<<< orphan*/  si_af; } ;
typedef  int /*<<< orphan*/  SVCXPRT ;

/* Variables and functions */
 int /*<<< orphan*/  AI_PASSIVE ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  LOG_WARNING ; 
 scalar_t__ NC_TPI_CLTS ; 
 scalar_t__ NC_TPI_COTS ; 
 scalar_t__ NC_TPI_COTS_ORD ; 
 int /*<<< orphan*/  NLM_PROG ; 
 int /*<<< orphan*/  NLM_SM ; 
 int /*<<< orphan*/  NLM_VERS ; 
 int /*<<< orphan*/  NLM_VERS4 ; 
 int /*<<< orphan*/  NLM_VERSX ; 
 int /*<<< orphan*/  RPC_MAXDATASIZE ; 
 int /*<<< orphan*/  SOMAXCONN ; 
 int /*<<< orphan*/  __rpc_nconf2sockinfo (struct netconfig*,struct __rpc_sockinfo*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  freeaddrinfo (struct addrinfo*) ; 
 int /*<<< orphan*/  gai_strerror (int) ; 
 int getaddrinfo (int /*<<< orphan*/ *,char*,struct addrinfo*,struct addrinfo**) ; 
 int /*<<< orphan*/  listen (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct addrinfo*,int /*<<< orphan*/ ,int) ; 
 int nhosts ; 
 int /*<<< orphan*/  nlm_prog_0 ; 
 int /*<<< orphan*/  nlm_prog_1 ; 
 int /*<<< orphan*/  nlm_prog_3 ; 
 int /*<<< orphan*/  nlm_prog_4 ; 
 int /*<<< orphan*/  rpcb_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct netconfig*,struct netbuf*) ; 
 int* sock_fd ; 
 scalar_t__ sock_fdcnt ; 
 scalar_t__ sock_fdpos ; 
 int /*<<< orphan*/  svc_reg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svc_tli_create (int,struct netconfig*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  xcreated ; 

__attribute__((used)) static void
complete_service(struct netconfig *nconf, char *port_str)
{
	struct addrinfo hints, *res = NULL;
	struct __rpc_sockinfo si;
	struct netbuf servaddr;
	SVCXPRT	*transp = NULL;
	int aicode, fd, nhostsbak;
	int registered = 0;

	if ((nconf->nc_semantics != NC_TPI_CLTS) &&
	    (nconf->nc_semantics != NC_TPI_COTS) &&
	    (nconf->nc_semantics != NC_TPI_COTS_ORD))
		return;	/* not my type */

	/*
	 * XXX - using RPC library internal functions.
	 */
	if (!__rpc_nconf2sockinfo(nconf, &si)) {
		syslog(LOG_ERR, "cannot get information for %s",
		    nconf->nc_netid);
		return;
	}

	nhostsbak = nhosts;
	while (nhostsbak > 0) {
		--nhostsbak;
		if (sock_fdpos >= sock_fdcnt) {
			/* Should never happen. */
			syslog(LOG_ERR, "Ran out of socket fd's");
			return;
		}
		fd = sock_fd[sock_fdpos++];
		if (fd < 0)
			continue;

		if (nconf->nc_semantics != NC_TPI_CLTS)
		    listen(fd, SOMAXCONN);

		transp = svc_tli_create(fd, nconf, NULL,
		    RPC_MAXDATASIZE, RPC_MAXDATASIZE);

		if (transp != (SVCXPRT *) NULL) {
			if (!svc_reg(transp, NLM_PROG, NLM_SM, nlm_prog_0,
			    NULL)) 
				syslog(LOG_ERR,
				    "can't register %s NLM_PROG, NLM_SM service",
				    nconf->nc_netid);
			
			if (!svc_reg(transp, NLM_PROG, NLM_VERS, nlm_prog_1,
			    NULL)) 
				syslog(LOG_ERR,
				    "can't register %s NLM_PROG, NLM_VERS service",
				    nconf->nc_netid);
			
			if (!svc_reg(transp, NLM_PROG, NLM_VERSX, nlm_prog_3,
			    NULL)) 
				syslog(LOG_ERR,
				    "can't register %s NLM_PROG, NLM_VERSX service",
				    nconf->nc_netid);
			
			if (!svc_reg(transp, NLM_PROG, NLM_VERS4, nlm_prog_4,
			    NULL)) 
				syslog(LOG_ERR,
				    "can't register %s NLM_PROG, NLM_VERS4 service",
				    nconf->nc_netid);
			
		} else 
			syslog(LOG_WARNING, "can't create %s services",
			    nconf->nc_netid);

		if (registered == 0) {
			registered = 1;
			memset(&hints, 0, sizeof hints);
			hints.ai_flags = AI_PASSIVE;
			hints.ai_family = si.si_af;
			hints.ai_socktype = si.si_socktype;
			hints.ai_protocol = si.si_proto;

			if ((aicode = getaddrinfo(NULL, port_str, &hints,
			    &res)) != 0) {
				syslog(LOG_ERR, "cannot get local address: %s",
				    gai_strerror(aicode));
				exit(1);
			}

			servaddr.buf = malloc(res->ai_addrlen);
			memcpy(servaddr.buf, res->ai_addr, res->ai_addrlen);
			servaddr.len = res->ai_addrlen;

			rpcb_set(NLM_PROG, NLM_SM, nconf, &servaddr);
			rpcb_set(NLM_PROG, NLM_VERS, nconf, &servaddr);
			rpcb_set(NLM_PROG, NLM_VERSX, nconf, &servaddr);
			rpcb_set(NLM_PROG, NLM_VERS4, nconf, &servaddr);

			xcreated++;
			freeaddrinfo(res);
		}
	} /* end while */
}