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
typedef  int /*<<< orphan*/  u_long ;
struct sockaddr_storage {int dummy; } ;
struct sockaddr_in6 {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {TYPE_2__ sin_addr; int /*<<< orphan*/  sin_family; } ;
struct sockaddr_dl {int sa_family; int sa_len; int sdl_len; } ;
struct sockaddr {int sa_family; int sa_len; int sdl_len; } ;
struct netent {int /*<<< orphan*/  n_net; } ;
struct ifaddrs {char* ifa_name; TYPE_1__* ifa_addr; struct ifaddrs* ifa_next; } ;
struct hostent {scalar_t__ h_length; int /*<<< orphan*/  h_addr; int /*<<< orphan*/  h_addrtype; } ;
struct addrinfo {int ai_family; int ai_addrlen; struct sockaddr_dl* ai_addr; int /*<<< orphan*/  ai_socktype; } ;
typedef  int /*<<< orphan*/  hints ;
struct TYPE_4__ {int sa_family; } ;

/* Variables and functions */
#define  AF_INET 134 
#define  AF_INET6 133 
#define  AF_LINK 132 
 int /*<<< orphan*/  EX_DATAERR ; 
 int /*<<< orphan*/  EX_NOHOST ; 
 int /*<<< orphan*/  EX_OSERR ; 
 int F_FORCEHOST ; 
 int F_FORCENET ; 
 int F_INTERFACE ; 
 scalar_t__ INADDR_ANY ; 
 int /*<<< orphan*/  INADDR_NONE ; 
 int /*<<< orphan*/  MIN (size_t,int) ; 
#define  PF_ROUTE 131 
#define  RTAX_DST 130 
#define  RTAX_GATEWAY 129 
#define  RTAX_IFP 128 
 int RTAX_MAX ; 
 size_t RTAX_NETMASK ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 scalar_t__ af ; 
 int aflen ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,char*,...) ; 
 int /*<<< orphan*/  freeaddrinfo (struct addrinfo*) ; 
 int /*<<< orphan*/  freeifaddrs (struct ifaddrs*) ; 
 int /*<<< orphan*/  gai_strerror (int) ; 
 int getaddrinfo (char*,int /*<<< orphan*/ *,struct addrinfo*,struct addrinfo**) ; 
 struct hostent* gethostbyname (char*) ; 
 int /*<<< orphan*/  getifaddrs (struct ifaddrs**) ; 
 struct netent* getnetbyname (char*) ; 
 int inet6_makenetandmask (struct sockaddr_in6*,char*) ; 
 scalar_t__ inet_aton (char*,TYPE_2__*) ; 
 scalar_t__ inet_lnaof (TYPE_2__) ; 
 int /*<<< orphan*/  inet_makenetandmask (int /*<<< orphan*/ ,struct sockaddr_in*,struct sockaddr_in*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inet_network (char*) ; 
 int /*<<< orphan*/  link_addr (char*,struct sockaddr_dl*) ; 
 int /*<<< orphan*/  memcpy (struct sockaddr_dl*,struct sockaddr_dl*,int) ; 
 int /*<<< orphan*/  memmove (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct addrinfo*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 int rtm_addrs ; 
 int /*<<< orphan*/ * so ; 
 int /*<<< orphan*/  sockaddr (char*,struct sockaddr_dl*,int) ; 
 char* strchr (char*,char) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strtoul (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage (char*) ; 

__attribute__((used)) static int
getaddr(int idx, char *str, struct hostent **hpp, int nrflags)
{
	struct sockaddr *sa;
#if defined(INET)
	struct sockaddr_in *sin;
	struct hostent *hp;
	struct netent *np;
	u_long val;
	char *q;
#elif defined(INET6)
	char *q;
#endif

	if (idx < 0 || idx >= RTAX_MAX)
		usage("internal error");
	if (af == 0) {
#if defined(INET)
		af = AF_INET;
		aflen = sizeof(struct sockaddr_in);
#elif defined(INET6)
		af = AF_INET6;
		aflen = sizeof(struct sockaddr_in6);
#else
		af = AF_LINK;
		aflen = sizeof(struct sockaddr_dl);
#endif
	}
#ifndef INET
	hpp = NULL;
#endif
	rtm_addrs |= (1 << idx);
	sa = (struct sockaddr *)&so[idx];
	sa->sa_family = af;
	sa->sa_len = aflen;

	switch (idx) {
	case RTAX_GATEWAY:
		if (nrflags & F_INTERFACE) {
			struct ifaddrs *ifap, *ifa;
			struct sockaddr_dl *sdl0 = (struct sockaddr_dl *)(void *)sa;
			struct sockaddr_dl *sdl = NULL;

			if (getifaddrs(&ifap))
				err(EX_OSERR, "getifaddrs");

			for (ifa = ifap; ifa != NULL; ifa = ifa->ifa_next) {
				if (ifa->ifa_addr->sa_family != AF_LINK)
					continue;

				if (strcmp(str, ifa->ifa_name) != 0)
					continue;

				sdl = (struct sockaddr_dl *)(void *)ifa->ifa_addr;
			}
			/* If we found it, then use it */
			if (sdl != NULL) {
				/*
				 * Note that we need to copy before calling
				 * freeifaddrs().
				 */
				memcpy(sdl0, sdl, sdl->sdl_len);
			}
			freeifaddrs(ifap);
			if (sdl != NULL)
				return(1);
			else
				errx(EX_DATAERR,
				    "interface '%s' does not exist", str);
		}
		break;
	case RTAX_IFP:
		sa->sa_family = AF_LINK;
		break;
	}
	if (strcmp(str, "default") == 0) {
		/*
		 * Default is net 0.0.0.0/0
		 */
		switch (idx) {
		case RTAX_DST:
			nrflags |= F_FORCENET;
			getaddr(RTAX_NETMASK, str, 0, nrflags);
			break;
		}
		return (0);
	}
	switch (sa->sa_family) {
#ifdef INET6
	case AF_INET6:
	{
		struct addrinfo hints, *res;
		int ecode;

		q = NULL;
		if (idx == RTAX_DST && (q = strchr(str, '/')) != NULL)
			*q = '\0';
		memset(&hints, 0, sizeof(hints));
		hints.ai_family = sa->sa_family;
		hints.ai_socktype = SOCK_DGRAM;
		ecode = getaddrinfo(str, NULL, &hints, &res);
		if (ecode != 0 || res->ai_family != AF_INET6 ||
		    res->ai_addrlen != sizeof(struct sockaddr_in6))
			errx(EX_OSERR, "%s: %s", str, gai_strerror(ecode));
		memcpy(sa, res->ai_addr, res->ai_addrlen);
		freeaddrinfo(res);
		if (q != NULL)
			*q++ = '/';
		if (idx == RTAX_DST)
			return (inet6_makenetandmask((struct sockaddr_in6 *)(void *)sa, q));
		return (0);
	}
#endif /* INET6 */
	case AF_LINK:
		link_addr(str, (struct sockaddr_dl *)(void *)sa);
		return (1);

	case PF_ROUTE:
		sockaddr(str, sa, sizeof(struct sockaddr_storage));
		return (1);
#ifdef INET
	case AF_INET:
#endif
	default:
		break;
	}

#ifdef INET
	sin = (struct sockaddr_in *)(void *)sa;
	if (hpp == NULL)
		hpp = &hp;
	*hpp = NULL;

	q = strchr(str,'/');
	if (q != NULL && idx == RTAX_DST) {
		*q = '\0';
		if ((val = inet_network(str)) != INADDR_NONE) {
			inet_makenetandmask(val, sin,
			    (struct sockaddr_in *)&so[RTAX_NETMASK],
			    strtoul(q+1, 0, 0));
			return (0);
		}
		*q = '/';
	}
	if ((idx != RTAX_DST || (nrflags & F_FORCENET) == 0) &&
	    inet_aton(str, &sin->sin_addr)) {
		val = sin->sin_addr.s_addr;
		if (idx != RTAX_DST || nrflags & F_FORCEHOST ||
		    inet_lnaof(sin->sin_addr) != INADDR_ANY)
			return (1);
		else {
			val = ntohl(val);
			goto netdone;
		}
	}
	if (idx == RTAX_DST && (nrflags & F_FORCEHOST) == 0 &&
	    ((val = inet_network(str)) != INADDR_NONE ||
	    ((np = getnetbyname(str)) != NULL && (val = np->n_net) != 0))) {
netdone:
		inet_makenetandmask(val, sin,
		    (struct sockaddr_in *)&so[RTAX_NETMASK], 0);
		return (0);
	}
	hp = gethostbyname(str);
	if (hp != NULL) {
		*hpp = hp;
		sin->sin_family = hp->h_addrtype;
		memmove((char *)&sin->sin_addr, hp->h_addr,
		    MIN((size_t)hp->h_length, sizeof(sin->sin_addr)));
		return (1);
	}
#endif
	errx(EX_NOHOST, "bad address: %s", str);
}