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
typedef  int u_int ;
struct sockaddr_in6 {int /*<<< orphan*/  sin6_addr; int /*<<< orphan*/  sin_addr; } ;
struct sockaddr_in {int /*<<< orphan*/  sin6_addr; int /*<<< orphan*/  sin_addr; } ;
struct nfsd_nfsd_args {char* addr; int addrlen; char* dnshost; int dnshostlen; char* dspath; int dspathlen; char* mdspath; int mdspathlen; } ;
struct addrinfo {int ai_flags; scalar_t__ ai_family; int ai_addrlen; char const* ai_canonname; TYPE_1__* ai_addr; struct addrinfo* ai_next; int /*<<< orphan*/  ai_protocol; int /*<<< orphan*/  ai_socktype; } ;
typedef  int /*<<< orphan*/  sin6 ;
typedef  int /*<<< orphan*/  sin ;
typedef  int /*<<< orphan*/  ip6 ;
typedef  int /*<<< orphan*/  hints ;
struct TYPE_2__ {scalar_t__ sa_family; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 int AI_ADDRCONFIG ; 
 int AI_CANONNAME ; 
 int /*<<< orphan*/  IN6_IS_ADDR_LINKLOCAL (int /*<<< orphan*/ *) ; 
 int INET6_ADDRSTRLEN ; 
 int /*<<< orphan*/  IPPROTO_TCP ; 
 scalar_t__ PF_UNSPEC ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  err (int,char*,...) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  freeaddrinfo (struct addrinfo*) ; 
 int /*<<< orphan*/  gai_strerror (int) ; 
 int getaddrinfo (char*,int /*<<< orphan*/ *,struct addrinfo*,struct addrinfo**) ; 
 char* inet_ntoa (int /*<<< orphan*/ ) ; 
 char* inet_ntop (scalar_t__,int /*<<< orphan*/ *,char*,int) ; 
 char* malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (struct sockaddr_in6*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  memset (struct addrinfo*,int /*<<< orphan*/ ,int) ; 
 char* realloc (char*,size_t) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,int) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 char* strdup (char const*) ; 
 void* strlen (char const*) ; 
 int /*<<< orphan*/  usage () ; 

__attribute__((used)) static void
parse_dsserver(const char *optionarg, struct nfsd_nfsd_args *nfsdargp)
{
	char *cp, *cp2, *dsaddr, *dshost, *dspath, *dsvol, nfsprt[9];
	char *mdspath, *mdsp, ip6[INET6_ADDRSTRLEN];
	const char *ad;
	int ecode;
	u_int adsiz, dsaddrcnt, dshostcnt, dspathcnt, hostsiz, pathsiz;
	u_int mdspathcnt;
	size_t dsaddrsiz, dshostsiz, dspathsiz, nfsprtsiz, mdspathsiz;
	struct addrinfo hints, *ai_tcp, *res;
	struct sockaddr_in sin;
	struct sockaddr_in6 sin6;

	cp = strdup(optionarg);
	if (cp == NULL)
		errx(1, "Out of memory");

	/* Now, do the host names. */
	dspathsiz = 1024;
	dspathcnt = 0;
	dspath = malloc(dspathsiz);
	if (dspath == NULL)
		errx(1, "Out of memory");
	dshostsiz = 1024;
	dshostcnt = 0;
	dshost = malloc(dshostsiz);
	if (dshost == NULL)
		errx(1, "Out of memory");
	dsaddrsiz = 1024;
	dsaddrcnt = 0;
	dsaddr = malloc(dsaddrsiz);
	if (dsaddr == NULL)
		errx(1, "Out of memory");
	mdspathsiz = 1024;
	mdspathcnt = 0;
	mdspath = malloc(mdspathsiz);
	if (mdspath == NULL)
		errx(1, "Out of memory");

	/* Put the NFS port# in "." form. */
	snprintf(nfsprt, 9, ".%d.%d", 2049 >> 8, 2049 & 0xff);
	nfsprtsiz = strlen(nfsprt);

	ai_tcp = NULL;
	/* Loop around for each DS server name. */
	do {
		cp2 = strchr(cp, ',');
		if (cp2 != NULL) {
			/* Not the last DS in the list. */
			*cp2++ = '\0';
			if (*cp2 == '\0')
				usage();
		}

		dsvol = strchr(cp, ':');
		if (dsvol == NULL || *(dsvol + 1) == '\0')
			usage();
		*dsvol++ = '\0';

		/* Optional path for MDS file system to be stored on DS. */
		mdsp = strchr(dsvol, '#');
		if (mdsp != NULL) {
			if (*(mdsp + 1) == '\0' || mdsp <= dsvol)
				usage();
			*mdsp++ = '\0';
		}

		/* Append this pathname to dspath. */
		pathsiz = strlen(dsvol);
		if (dspathcnt + pathsiz + 1 > dspathsiz) {
			dspathsiz *= 2;
			dspath = realloc(dspath, dspathsiz);
			if (dspath == NULL)
				errx(1, "Out of memory");
		}
		strcpy(&dspath[dspathcnt], dsvol);
		dspathcnt += pathsiz + 1;

		/* Append this pathname to mdspath. */
		if (mdsp != NULL)
			pathsiz = strlen(mdsp);
		else
			pathsiz = 0;
		if (mdspathcnt + pathsiz + 1 > mdspathsiz) {
			mdspathsiz *= 2;
			mdspath = realloc(mdspath, mdspathsiz);
			if (mdspath == NULL)
				errx(1, "Out of memory");
		}
		if (mdsp != NULL)
			strcpy(&mdspath[mdspathcnt], mdsp);
		else
			mdspath[mdspathcnt] = '\0';
		mdspathcnt += pathsiz + 1;

		if (ai_tcp != NULL)
			freeaddrinfo(ai_tcp);

		/* Get the fully qualified domain name and IP address. */
		memset(&hints, 0, sizeof(hints));
		hints.ai_flags = AI_CANONNAME | AI_ADDRCONFIG;
		hints.ai_family = PF_UNSPEC;
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_protocol = IPPROTO_TCP;
		ecode = getaddrinfo(cp, NULL, &hints, &ai_tcp);
		if (ecode != 0)
			err(1, "getaddrinfo pnfs: %s %s", cp,
			    gai_strerror(ecode));
		ad = NULL;
		for (res = ai_tcp; res != NULL; res = res->ai_next) {
			if (res->ai_addr->sa_family == AF_INET) {
				if (res->ai_addrlen < sizeof(sin))
					err(1, "getaddrinfo() returned "
					    "undersized IPv4 address");
				/*
				 * Mips cares about sockaddr_in alignment,
				 * so copy the address.
				 */
				memcpy(&sin, res->ai_addr, sizeof(sin));
				ad = inet_ntoa(sin.sin_addr);
				break;
			} else if (res->ai_family == AF_INET6) {
				if (res->ai_addrlen < sizeof(sin6))
					err(1, "getaddrinfo() returned "
					    "undersized IPv6 address");
				/*
				 * Mips cares about sockaddr_in6 alignment,
				 * so copy the address.
				 */
				memcpy(&sin6, res->ai_addr, sizeof(sin6));
				ad = inet_ntop(AF_INET6, &sin6.sin6_addr, ip6,
				    sizeof(ip6));

				/*
				 * XXX
				 * Since a link local address will only
				 * work if the client and DS are in the
				 * same scope zone, only use it if it is
				 * the only address.
				 */
				if (ad != NULL &&
				    !IN6_IS_ADDR_LINKLOCAL(&sin6.sin6_addr))
					break;
			}
		}
		if (ad == NULL)
			err(1, "No IP address for %s", cp);

		/* Append this address to dsaddr. */
		adsiz = strlen(ad);
		if (dsaddrcnt + adsiz + nfsprtsiz + 1 > dsaddrsiz) {
			dsaddrsiz *= 2;
			dsaddr = realloc(dsaddr, dsaddrsiz);
			if (dsaddr == NULL)
				errx(1, "Out of memory");
		}
		strcpy(&dsaddr[dsaddrcnt], ad);
		strcat(&dsaddr[dsaddrcnt], nfsprt);
		dsaddrcnt += adsiz + nfsprtsiz + 1;

		/* Append this hostname to dshost. */
		hostsiz = strlen(ai_tcp->ai_canonname);
		if (dshostcnt + hostsiz + 1 > dshostsiz) {
			dshostsiz *= 2;
			dshost = realloc(dshost, dshostsiz);
			if (dshost == NULL)
				errx(1, "Out of memory");
		}
		strcpy(&dshost[dshostcnt], ai_tcp->ai_canonname);
		dshostcnt += hostsiz + 1;

		cp = cp2;
	} while (cp != NULL);

	nfsdargp->addr = dsaddr;
	nfsdargp->addrlen = dsaddrcnt;
	nfsdargp->dnshost = dshost;
	nfsdargp->dnshostlen = dshostcnt;
	nfsdargp->dspath = dspath;
	nfsdargp->dspathlen = dspathcnt;
	nfsdargp->mdspath = mdspath;
	nfsdargp->mdspathlen = mdspathcnt;
	freeaddrinfo(ai_tcp);
}