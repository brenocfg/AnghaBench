#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_short ;
typedef  int /*<<< orphan*/  u_int32_t ;
struct TYPE_7__ {int /*<<< orphan*/ * s6_addr; } ;
struct sockaddr_in6 {TYPE_2__ sin6_addr; } ;
struct TYPE_6__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {TYPE_1__ sin_addr; int /*<<< orphan*/  sin_port; } ;
struct sockaddr {int sa_family; } ;
struct servent {char* s_name; } ;
struct hostent {char* h_name; } ;
struct afd {int a_off; int /*<<< orphan*/  a_af; int /*<<< orphan*/  a_addrlen; } ;
typedef  int /*<<< orphan*/  socklen_t ;
typedef  int /*<<< orphan*/  numserv ;
typedef  int /*<<< orphan*/  numaddr ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int EAI_MEMORY ; 
 int EAI_NONAME ; 
 int EAI_SYSTEM ; 
 int /*<<< orphan*/  IN6_IS_ADDR_LINKLOCAL (TYPE_2__*) ; 
 int /*<<< orphan*/  IN6_IS_ADDR_LOOPBACK (TYPE_2__*) ; 
 int /*<<< orphan*/  IN6_IS_ADDR_MULTICAST (TYPE_2__*) ; 
 int /*<<< orphan*/  IN6_IS_ADDR_V4MAPPED (TYPE_2__*) ; 
 int /*<<< orphan*/  IN_EXPERIMENTAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IN_MULTICAST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IN_ZERONET (int /*<<< orphan*/ ) ; 
 int NI_DGRAM ; 
 int NI_NAMEREQD ; 
 int NI_NOFQDN ; 
 int NI_NUMERICHOST ; 
 int NI_NUMERICSERV ; 
 int /*<<< orphan*/  freehostent (struct hostent*) ; 
 struct hostent* getipnodebyaddr (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 struct servent* getservbyport (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * inet_ntop (int /*<<< orphan*/ ,char const*,char*,size_t) ; 
 int ip6_parsenumeric (struct sockaddr const*,char const*,char*,size_t,int) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,size_t) ; 
 int strlen (char*) ; 

__attribute__((used)) static int
getnameinfo_inet(const struct afd *afd,
    const struct sockaddr *sa, socklen_t salen,
    char *host, size_t hostlen, char *serv, size_t servlen,
    int flags)
{
	struct servent *sp;
	struct hostent *hp;
	u_short port;
	const char *addr;
	u_int32_t v4a;
	int h_error;
	char numserv[512];
	char numaddr[512];

	/* network byte order */
	port = ((const struct sockaddr_in *)sa)->sin_port;
	addr = (const char *)sa + afd->a_off;

	if (serv == NULL || servlen == 0) {
		/*
		 * do nothing in this case.
		 * in case you are wondering if "&&" is more correct than
		 * "||" here: rfc2553bis-03 says that serv == NULL OR
		 * servlen == 0 means that the caller does not want the result.
		 */
	} else {
		if (flags & NI_NUMERICSERV)
			sp = NULL;
		else {
			sp = getservbyport(port,
				(flags & NI_DGRAM) ? "udp" : "tcp");
		}
		if (sp) {
			if (strlen(sp->s_name) + 1 > servlen)
				return EAI_MEMORY;
			strlcpy(serv, sp->s_name, servlen);
		} else {
			snprintf(numserv, sizeof(numserv), "%u", ntohs(port));
			if (strlen(numserv) + 1 > servlen)
				return EAI_MEMORY;
			strlcpy(serv, numserv, servlen);
		}
	}

	switch (sa->sa_family) {
	case AF_INET:
		v4a = (u_int32_t)
		    ntohl(((const struct sockaddr_in *)sa)->sin_addr.s_addr);
		if (IN_MULTICAST(v4a) || IN_EXPERIMENTAL(v4a) ||
		    IN_ZERONET(v4a))
			flags |= NI_NUMERICHOST;
		break;
#ifdef INET6
	case AF_INET6:
	    {
		const struct sockaddr_in6 *sin6;
		sin6 = (const struct sockaddr_in6 *)sa;
		switch (sin6->sin6_addr.s6_addr[0]) {
		case 0x00:
			if (IN6_IS_ADDR_V4MAPPED(&sin6->sin6_addr))
				;
			else if (IN6_IS_ADDR_LOOPBACK(&sin6->sin6_addr))
				;
			else
				flags |= NI_NUMERICHOST;
			break;
		default:
			if (IN6_IS_ADDR_LINKLOCAL(&sin6->sin6_addr)) {
				flags |= NI_NUMERICHOST;
			}
			else if (IN6_IS_ADDR_MULTICAST(&sin6->sin6_addr))
				flags |= NI_NUMERICHOST;
			break;
		}
	    }
		break;
#endif
	}
	if (host == NULL || hostlen == 0) {
		/*
		 * do nothing in this case.
		 * in case you are wondering if "&&" is more correct than
		 * "||" here: rfc2553bis-03 says that host == NULL or
		 * hostlen == 0 means that the caller does not want the result.
		 */
	} else if (flags & NI_NUMERICHOST) {
		size_t numaddrlen;

		/* NUMERICHOST and NAMEREQD conflicts with each other */
		if (flags & NI_NAMEREQD)
			return EAI_NONAME;

		switch(afd->a_af) {
#ifdef INET6
		case AF_INET6:
		{
			int error;

			if ((error = ip6_parsenumeric(sa, addr, host,
						      hostlen, flags)) != 0)
				return(error);
			break;
		}
#endif
		default:
			if (inet_ntop(afd->a_af, addr, numaddr, sizeof(numaddr))
			    == NULL)
				return EAI_SYSTEM;
			numaddrlen = strlen(numaddr);
			if (numaddrlen + 1 > hostlen) /* don't forget terminator */
				return EAI_MEMORY;
			strlcpy(host, numaddr, hostlen);
			break;
		}
	} else {
		hp = getipnodebyaddr(addr, afd->a_addrlen, afd->a_af, &h_error);

		if (hp) {
#if 0
			/*
			 * commented out, since "for local host" is not
			 * implemented here - see RFC2553 p30
			 */
			if (flags & NI_NOFQDN) {
				char *p;
				p = strchr(hp->h_name, '.');
				if (p)
					*p = '\0';
			}
#endif
			if (strlen(hp->h_name) + 1 > hostlen) {
				freehostent(hp);
				return EAI_MEMORY;
			}
			strlcpy(host, hp->h_name, hostlen);
			freehostent(hp);
		} else {
			if (flags & NI_NAMEREQD)
				return EAI_NONAME;
			switch(afd->a_af) {
#ifdef INET6
			case AF_INET6:
			{
				int error;

				if ((error = ip6_parsenumeric(sa, addr, host,
							      hostlen,
							      flags)) != 0)
					return(error);
				break;
			}
#endif
			default:
				if (inet_ntop(afd->a_af, addr, host,
				    hostlen) == NULL)
					return EAI_SYSTEM;
				break;
			}
		}
	}
	return(0);
}