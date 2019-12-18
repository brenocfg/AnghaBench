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
typedef  int /*<<< orphan*/  u_int32_t ;
struct netbuf {int len; int maxlen; struct sockaddr* buf; } ;
struct t_bind {struct netbuf addr; } ;
struct sockaddr_un {int ai_family; int ai_addrlen; scalar_t__ ai_addr; int /*<<< orphan*/  ai_flags; int /*<<< orphan*/  ai_protocol; int /*<<< orphan*/  ai_socktype; int /*<<< orphan*/  sun_len; int /*<<< orphan*/  sun_path; int /*<<< orphan*/  sun_family; } ;
struct sockaddr {int sa_len; } ;
typedef  char pmaplist ;
struct netconfig {scalar_t__ nc_semantics; char* nc_netid; int nc_nlookups; char** nc_lookups; char* nc_protofmly; char* nc_proto; } ;
struct addrinfo {int ai_family; int ai_addrlen; scalar_t__ ai_addr; int /*<<< orphan*/  ai_flags; int /*<<< orphan*/  ai_protocol; int /*<<< orphan*/  ai_socktype; int /*<<< orphan*/  sun_len; int /*<<< orphan*/  sun_path; int /*<<< orphan*/  sun_family; } ;
struct __rpc_sockinfo {int si_af; int /*<<< orphan*/  si_proto; int /*<<< orphan*/  si_socktype; } ;
typedef  int mode_t ;
struct TYPE_2__ {void* pm_vers; void* pm_prot; int /*<<< orphan*/  pm_port; int /*<<< orphan*/  pm_prog; } ;
typedef  int /*<<< orphan*/  SVCXPRT ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int /*<<< orphan*/  AF_LOCAL ; 
 int /*<<< orphan*/  AI_NUMERICHOST ; 
 int /*<<< orphan*/  AI_PASSIVE ; 
 scalar_t__ EAFNOSUPPORT ; 
 int /*<<< orphan*/  IPPROTO_IPV6 ; 
 void* IPPROTO_ST ; 
 void* IPPROTO_TCP ; 
 void* IPPROTO_UDP ; 
 int /*<<< orphan*/  IPV6_V6ONLY ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  LOG_ERR ; 
 char* NC_INET ; 
 char* NC_TCP ; 
 scalar_t__ NC_TPI_CLTS ; 
 scalar_t__ NC_TPI_COTS ; 
 scalar_t__ NC_TPI_COTS_ORD ; 
 char* NC_UDP ; 
 int /*<<< orphan*/  PMAPPORT ; 
 int /*<<< orphan*/  PMAPPROG ; 
 void* PMAPVERS ; 
 int /*<<< orphan*/  RPCBPROG ; 
 void* RPCBVERS ; 
 void* RPCBVERS4 ; 
 int /*<<< orphan*/  RPC_MAXDATASIZE ; 
 int /*<<< orphan*/  SOMAXCONN ; 
 int /*<<< orphan*/  SUN_LEN (struct sockaddr_un*) ; 
 int S_IXGRP ; 
 int S_IXOTH ; 
 int S_IXUSR ; 
 int /*<<< orphan*/  _PATH_RPCBINDSOCK ; 
 int __rpc_nconf2fd (struct netconfig*) ; 
 int /*<<< orphan*/  __rpc_nconf2sockinfo (struct netconfig*,struct __rpc_sockinfo*) ; 
 int add_bndlist (struct netconfig*,struct netbuf*) ; 
 scalar_t__ bind (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int create_rmtcall_fd (struct netconfig*) ; 
 scalar_t__ debugging ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  freeaddrinfo (struct sockaddr_un*) ; 
 int /*<<< orphan*/  gai_strerror (int) ; 
 int getaddrinfo (char*,int /*<<< orphan*/ ,struct sockaddr_un*,struct sockaddr_un**) ; 
 char** hosts ; 
 int inet_pton (int const,char*,int /*<<< orphan*/ *) ; 
 char* list_pml ; 
 int /*<<< orphan*/  listen (int,int /*<<< orphan*/ ) ; 
 void* malloc (int) ; 
 int /*<<< orphan*/  memcpy (struct sockaddr*,struct sockaddr*,int) ; 
 int /*<<< orphan*/  memset (struct sockaddr_un*,int /*<<< orphan*/ ,int) ; 
 int nhosts ; 
 int /*<<< orphan*/  on ; 
 int /*<<< orphan*/  pmap_service ; 
 int /*<<< orphan*/  rbllist_add (int /*<<< orphan*/ ,void*,struct netconfig*,struct netbuf*) ; 
 char** realloc (char**,int) ; 
 int /*<<< orphan*/  rpcb_service_3 ; 
 int /*<<< orphan*/  rpcb_service_4 ; 
 int /*<<< orphan*/  servname ; 
 int /*<<< orphan*/  setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* strdup (char*) ; 
 int /*<<< orphan*/  svc_reg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svc_register (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ svc_tli_create (int,struct netconfig*,struct t_bind*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,...) ; 
 void* taddr2uaddr (struct netconfig*,struct netbuf*) ; 
 void* tcp_uaddr ; 
 scalar_t__* tcptrans ; 
 void* udp_uaddr ; 
 scalar_t__* udptrans ; 
 int umask (int) ; 
 int /*<<< orphan*/  unlink (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
init_transport(struct netconfig *nconf)
{
	int fd;
	struct t_bind taddr;
	struct addrinfo hints, *res = NULL;
	struct __rpc_sockinfo si;
	SVCXPRT	*my_xprt;
	int status;	/* bound checking ? */
	int aicode;
	int addrlen;
	int nhostsbak;
	int bound;
	struct sockaddr *sa;
	u_int32_t host_addr[4];  /* IPv4 or IPv6 */
	struct sockaddr_un sun;
	mode_t oldmask;

	if ((nconf->nc_semantics != NC_TPI_CLTS) &&
	    (nconf->nc_semantics != NC_TPI_COTS) &&
	    (nconf->nc_semantics != NC_TPI_COTS_ORD))
	    return (1);	/* not my type */
#ifdef ND_DEBUG
	if (debugging) {
	    int i;
	    char **s;

	    (void)fprintf(stderr, "%s: %ld lookup routines :\n",
		nconf->nc_netid, nconf->nc_nlookups);
	    for (i = 0, s = nconf->nc_lookups; i < nconf->nc_nlookups;
		i++, s++)
		fprintf(stderr, "[%d] - %s\n", i, *s);
	}
#endif

	/*
	 * XXX - using RPC library internal functions.
	 */
	if ((strcmp(nconf->nc_netid, "local") == 0) ||
	    (strcmp(nconf->nc_netid, "unix") == 0)) {
	    /* 
	     * For other transports we call this later, for each socket we
	     * like to bind.
	     */
	    if ((fd = __rpc_nconf2fd(nconf)) < 0) {
		int non_fatal = 0;
		if (errno == EAFNOSUPPORT)
		    non_fatal = 1;
		syslog(non_fatal?LOG_DEBUG:LOG_ERR, "cannot create socket for %s",
		    nconf->nc_netid);
		return (1);
	    }
	}

	if (!__rpc_nconf2sockinfo(nconf, &si)) {
	    syslog(LOG_ERR, "cannot get information for %s",
		nconf->nc_netid);
	    return (1);
	}

	if ((strcmp(nconf->nc_netid, "local") == 0) ||
	    (strcmp(nconf->nc_netid, "unix") == 0)) {
	    memset(&sun, 0, sizeof sun);
	    sun.sun_family = AF_LOCAL;
	    unlink(_PATH_RPCBINDSOCK);
	    strcpy(sun.sun_path, _PATH_RPCBINDSOCK);
	    sun.sun_len = SUN_LEN(&sun);
	    addrlen = sizeof (struct sockaddr_un);
	    sa = (struct sockaddr *)&sun;
	} else {
	    /* Get rpcbind's address on this transport */

	    memset(&hints, 0, sizeof hints);
	    hints.ai_flags = AI_PASSIVE;
	    hints.ai_family = si.si_af;
	    hints.ai_socktype = si.si_socktype;
	    hints.ai_protocol = si.si_proto;
	}

	if ((strcmp(nconf->nc_netid, "local") != 0) &&
	    (strcmp(nconf->nc_netid, "unix") != 0)) {
	    /*
	     * If no hosts were specified, just bind to INADDR_ANY.
	     * Otherwise  make sure 127.0.0.1 is added to the list.
	     */
	    nhostsbak = nhosts + 1;
	    hosts = realloc(hosts, nhostsbak * sizeof(char *));
	    if (nhostsbak == 1)
	        hosts[0] = "*";
	    else {
		if (hints.ai_family == AF_INET) {
		    hosts[nhostsbak - 1] = "127.0.0.1";
		} else if (hints.ai_family == AF_INET6) {
		    hosts[nhostsbak - 1] = "::1";
		} else
		    return 1;
	    }

	    /*
	     * Bind to specific IPs if asked to
	     */
	    bound = 0;
	    while (nhostsbak > 0) {
		--nhostsbak;
		/*
		 * XXX - using RPC library internal functions.
		 */
		if ((fd = __rpc_nconf2fd(nconf)) < 0) {
		    int non_fatal = 0;
		    if (errno == EAFNOSUPPORT &&
			nconf->nc_semantics != NC_TPI_CLTS) 
			non_fatal = 1;
		    syslog(non_fatal ? LOG_DEBUG : LOG_ERR, 
			"cannot create socket for %s", nconf->nc_netid);
		    return (1);
		}
		switch (hints.ai_family) {
		case AF_INET:
		    if (inet_pton(AF_INET, hosts[nhostsbak],
			host_addr) == 1) {
			hints.ai_flags &= AI_NUMERICHOST;
		    } else {
			/*
			 * Skip if we have an AF_INET6 address.
			 */
			if (inet_pton(AF_INET6,
			    hosts[nhostsbak], host_addr) == 1) {
			    close(fd);
			    continue;
			}
		    }
		    break;
		case AF_INET6:
		    if (inet_pton(AF_INET6, hosts[nhostsbak],
			host_addr) == 1) {
			hints.ai_flags &= AI_NUMERICHOST;
		    } else {
			/*
			 * Skip if we have an AF_INET address.
			 */
			if (inet_pton(AF_INET, hosts[nhostsbak],
			    host_addr) == 1) {
				close(fd);
				continue;
			}
		    }
		    if (setsockopt(fd, IPPROTO_IPV6,
			IPV6_V6ONLY, &on, sizeof on) < 0) {
			syslog(LOG_ERR,
			    "can't set v6-only binding for "
			    "ipv6 socket: %m");
			continue;
		    }
		    break;
		default:
		    break;
		}

		/*
		 * If no hosts were specified, just bind to INADDR_ANY
		 */
		if (strcmp("*", hosts[nhostsbak]) == 0)
		    hosts[nhostsbak] = NULL;
		if ((strcmp(nconf->nc_netid, "local") != 0) &&
		    (strcmp(nconf->nc_netid, "unix") != 0)) {
		    if ((aicode = getaddrinfo(hosts[nhostsbak],
			servname, &hints, &res)) != 0) {
			syslog(LOG_ERR,
			    "cannot get local address for %s: %s",
			    nconf->nc_netid, gai_strerror(aicode));
			continue;
		    }
		    addrlen = res->ai_addrlen;
		    sa = (struct sockaddr *)res->ai_addr;
		}
		oldmask = umask(S_IXUSR|S_IXGRP|S_IXOTH);
		if (bind(fd, sa, addrlen) != 0) {
		    syslog(LOG_ERR, "cannot bind %s on %s: %m",
			(hosts[nhostsbak] == NULL) ? "*" :
			    hosts[nhostsbak], nconf->nc_netid);
		    if (res != NULL)
			freeaddrinfo(res);
		    continue;
		} else
		    bound = 1;
		(void)umask(oldmask);

		/* Copy the address */
		taddr.addr.len = taddr.addr.maxlen = addrlen;
		taddr.addr.buf = malloc(addrlen);
		if (taddr.addr.buf == NULL) {
		    syslog(LOG_ERR,
			"cannot allocate memory for %s address",
			nconf->nc_netid);
		    if (res != NULL)
			freeaddrinfo(res);
		    return 1;
		}
		memcpy(taddr.addr.buf, sa, addrlen);
#ifdef ND_DEBUG
		if (debugging) {
		    /*
		     * for debugging print out our universal
		     * address
		     */
		    char *uaddr;
		    struct netbuf nb;

		    nb.buf = sa;
		    nb.len = nb.maxlen = sa->sa_len;
		    uaddr = taddr2uaddr(nconf, &nb);
		    (void)fprintf(stderr,
			"rpcbind : my address is %s\n", uaddr);
		    (void)free(uaddr);
		}
#endif

		if (nconf->nc_semantics != NC_TPI_CLTS)
		    listen(fd, SOMAXCONN);

		my_xprt = (SVCXPRT *)svc_tli_create(fd, nconf, &taddr,
		    RPC_MAXDATASIZE, RPC_MAXDATASIZE);
		if (my_xprt == (SVCXPRT *)NULL) {
		    syslog(LOG_ERR, "%s: could not create service",
			nconf->nc_netid);
		    goto error;
		}
	    }
	    if (!bound)
		return 1;
	} else {
	    oldmask = umask(S_IXUSR|S_IXGRP|S_IXOTH);
	    if (bind(fd, sa, addrlen) < 0) {
		syslog(LOG_ERR, "cannot bind %s: %m", nconf->nc_netid);
		if (res != NULL)
		    freeaddrinfo(res);
		return 1;
	    }
	    (void) umask(oldmask);

	    /* Copy the address */
	    taddr.addr.len = taddr.addr.maxlen = addrlen;
	    taddr.addr.buf = malloc(addrlen);
	    if (taddr.addr.buf == NULL) {
		syslog(LOG_ERR, "cannot allocate memory for %s address",
		    nconf->nc_netid);
		if (res != NULL)
		    freeaddrinfo(res);
		return 1;
	    }
	    memcpy(taddr.addr.buf, sa, addrlen);
#ifdef ND_DEBUG
	    if (debugging) {
		/* for debugging print out our universal address */
		char *uaddr;
		struct netbuf nb;

		nb.buf = sa;
		nb.len = nb.maxlen = sa->sa_len;
		uaddr = taddr2uaddr(nconf, &nb);
		(void) fprintf(stderr, "rpcbind : my address is %s\n",
		    uaddr);
		(void) free(uaddr);
	    }
#endif

	    if (nconf->nc_semantics != NC_TPI_CLTS)
		listen(fd, SOMAXCONN);

	    my_xprt = (SVCXPRT *)svc_tli_create(fd, nconf, &taddr,
		RPC_MAXDATASIZE, RPC_MAXDATASIZE);
	    if (my_xprt == (SVCXPRT *)NULL) {
		syslog(LOG_ERR, "%s: could not create service",
		    nconf->nc_netid);
		goto error;
	    }
	}

#ifdef PORTMAP
	/*
	 * Register both the versions for tcp/ip, udp/ip and local.
	 */
	if ((strcmp(nconf->nc_protofmly, NC_INET) == 0 &&
		(strcmp(nconf->nc_proto, NC_TCP) == 0 ||
		strcmp(nconf->nc_proto, NC_UDP) == 0)) ||
		(strcmp(nconf->nc_netid, "unix") == 0) ||
		(strcmp(nconf->nc_netid, "local") == 0)) {
		struct pmaplist *pml;

		if (!svc_register(my_xprt, PMAPPROG, PMAPVERS,
			pmap_service, 0)) {
			syslog(LOG_ERR, "could not register on %s",
					nconf->nc_netid);
			goto error;
		}
		pml = malloc(sizeof (struct pmaplist));
		if (pml == NULL) {
			syslog(LOG_ERR, "no memory!");
			exit(1);
		}
		pml->pml_map.pm_prog = PMAPPROG;
		pml->pml_map.pm_vers = PMAPVERS;
		pml->pml_map.pm_port = PMAPPORT;
		if (strcmp(nconf->nc_proto, NC_TCP) == 0) {
			if (tcptrans[0]) {
				free(pml);
				pml = NULL;
				syslog(LOG_ERR,
				"cannot have more than one TCP transport");
				goto error;
			}
			tcptrans = strdup(nconf->nc_netid);
			pml->pml_map.pm_prot = IPPROTO_TCP;

			/* Let's snarf the universal address */
			/* "h1.h2.h3.h4.p1.p2" */
			tcp_uaddr = taddr2uaddr(nconf, &taddr.addr);
		} else if (strcmp(nconf->nc_proto, NC_UDP) == 0) {
			if (udptrans[0]) {
				syslog(LOG_ERR,
				"cannot have more than one UDP transport");
				goto error;
			}
			udptrans = strdup(nconf->nc_netid);
			pml->pml_map.pm_prot = IPPROTO_UDP;

			/* Let's snarf the universal address */
			/* "h1.h2.h3.h4.p1.p2" */
			udp_uaddr = taddr2uaddr(nconf, &taddr.addr);
		} else if (strcmp(nconf->nc_netid, "local") == 0)
			pml->pml_map.pm_prot = IPPROTO_ST;
		else if (strcmp(nconf->nc_netid, "unix") == 0)
			pml->pml_map.pm_prot = IPPROTO_ST;
		pml->pml_next = list_pml;
		list_pml = pml;

		/* Add version 3 information */
		pml = malloc(sizeof (struct pmaplist));
		if (pml == NULL) {
			syslog(LOG_ERR, "no memory!");
			exit(1);
		}
		pml->pml_map = list_pml->pml_map;
		pml->pml_map.pm_vers = RPCBVERS;
		pml->pml_next = list_pml;
		list_pml = pml;

		/* Add version 4 information */
		pml = malloc (sizeof (struct pmaplist));
		if (pml == NULL) {
			syslog(LOG_ERR, "no memory!");
			exit(1);
		}
		pml->pml_map = list_pml->pml_map;
		pml->pml_map.pm_vers = RPCBVERS4;
		pml->pml_next = list_pml;
		list_pml = pml;

		/* Also add version 2 stuff to rpcbind list */
		rbllist_add(PMAPPROG, PMAPVERS, nconf, &taddr.addr);
	}
#endif

	/* version 3 registration */
	if (!svc_reg(my_xprt, RPCBPROG, RPCBVERS, rpcb_service_3, NULL)) {
		syslog(LOG_ERR, "could not register %s version 3",
				nconf->nc_netid);
		goto error;
	}
	rbllist_add(RPCBPROG, RPCBVERS, nconf, &taddr.addr);

	/* version 4 registration */
	if (!svc_reg(my_xprt, RPCBPROG, RPCBVERS4, rpcb_service_4, NULL)) {
		syslog(LOG_ERR, "could not register %s version 4",
				nconf->nc_netid);
		goto error;
	}
	rbllist_add(RPCBPROG, RPCBVERS4, nconf, &taddr.addr);

	/* decide if bound checking works for this transport */
	status = add_bndlist(nconf, &taddr.addr);
#ifdef BIND_DEBUG
	if (debugging) {
		if (status < 0) {
			fprintf(stderr, "Error in finding bind status for %s\n",
				nconf->nc_netid);
		} else if (status == 0) {
			fprintf(stderr, "check binding for %s\n",
				nconf->nc_netid);
		} else if (status > 0) {
			fprintf(stderr, "No check binding for %s\n",
				nconf->nc_netid);
		}
	}
#endif
	/*
	 * rmtcall only supported on CLTS transports for now.
	 */
	if (nconf->nc_semantics == NC_TPI_CLTS) {
		status = create_rmtcall_fd(nconf);

#ifdef BIND_DEBUG
		if (debugging) {
			if (status < 0) {
				fprintf(stderr,
				    "Could not create rmtcall fd for %s\n",
					nconf->nc_netid);
			} else {
				fprintf(stderr, "rmtcall fd for %s is %d\n",
					nconf->nc_netid, status);
			}
		}
#endif
	}
	return (0);
error:
	close(fd);
	return (1);
}