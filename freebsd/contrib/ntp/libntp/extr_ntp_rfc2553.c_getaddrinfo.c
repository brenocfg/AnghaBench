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
struct sockaddr_in6 {unsigned short sin6_port; } ;
struct sockaddr_in {unsigned short sin_port; } ;
struct servent {int s_port; int /*<<< orphan*/  s_proto; } ;
struct addrinfo {int ai_flags; int ai_family; int ai_socktype; int ai_protocol; scalar_t__ ai_addr; } ;

/* Variables and functions */
#define  AF_INET 134 
#define  AF_INET6 133 
#define  AF_LOCAL 132 
#define  AF_UNSPEC 131 
 int EAI_FAMILY ; 
 int EAI_MEMORY ; 
 int EAI_NONAME ; 
 int EAI_SERVICE ; 
 int EAI_SOCKTYPE ; 
#define  SOCK_DGRAM 130 
#define  SOCK_RAW 129 
#define  SOCK_STREAM 128 
 struct addrinfo* calloc (int,int) ; 
 int do_nodename (char const*,struct addrinfo*,struct addrinfo const*) ; 
 int /*<<< orphan*/  freeaddrinfo (struct addrinfo*) ; 
 struct servent* getservbyname (char const*,char const*) ; 
 int htons (unsigned short) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int strtol (char const*,char**,int) ; 

int
getaddrinfo (const char *nodename, const char *servname,
	const struct addrinfo *hints, struct addrinfo **res)
{
	int rval;
	struct servent *sp;
	struct addrinfo *ai = NULL;
	int port;
	const char *proto = NULL;
	int family, socktype, flags, protocol;


	/*
	 * If no name is provide just return an error
	 */
	if (nodename == NULL && servname == NULL)
		return (EAI_NONAME);
	
	ai = calloc(sizeof(struct addrinfo), 1);
	if (ai == NULL)
		return (EAI_MEMORY);

	/*
	 * Copy default values from hints, if available
	 */
	if (hints != NULL) {
		ai->ai_flags = hints->ai_flags;
		ai->ai_family = hints->ai_family;
		ai->ai_socktype = hints->ai_socktype;
		ai->ai_protocol = hints->ai_protocol;

		family = hints->ai_family;
		socktype = hints->ai_socktype;
		protocol = hints->ai_protocol;
		flags = hints->ai_flags;

		switch (family) {
		case AF_UNSPEC:
			switch (hints->ai_socktype) {
			case SOCK_STREAM:
				proto = "tcp";
				break;
			case SOCK_DGRAM:
				proto = "udp";
				break;
			}
			break;
		case AF_INET:
		case AF_INET6:
			switch (hints->ai_socktype) {
			case 0:
				break;
			case SOCK_STREAM:
				proto = "tcp";
				break;
			case SOCK_DGRAM:
				proto = "udp";
				break;
			case SOCK_RAW:
				break;
			default:
				return (EAI_SOCKTYPE);
			}
			break;
#ifdef	AF_LOCAL
		case AF_LOCAL:
			switch (hints->ai_socktype) {
			case 0:
				break;
			case SOCK_STREAM:
				break;
			case SOCK_DGRAM:
				break;
			default:
				return (EAI_SOCKTYPE);
			}
			break;
#endif
		default:
			return (EAI_FAMILY);
		}
	} else {
		protocol = 0;
		family = 0;
		socktype = 0;
		flags = 0;
	}

	rval = do_nodename(nodename, ai, hints);
	if (rval != 0) {
		freeaddrinfo(ai);
		return (rval);
	}

	/*
	 * First, look up the service name (port) if it was
	 * requested.  If the socket type wasn't specified, then
	 * try and figure it out.
	 */
	if (servname != NULL) {
		char *e;

		port = strtol(servname, &e, 10);
		if (*e == '\0') {
			if (socktype == 0)
				return (EAI_SOCKTYPE);
			if (port < 0 || port > 65535)
				return (EAI_SERVICE);
			port = htons((unsigned short) port);
		} else {
			sp = getservbyname(servname, proto);
			if (sp == NULL)
				return (EAI_SERVICE);
			port = sp->s_port;
			if (socktype == 0) {
				if (strcmp(sp->s_proto, "tcp") == 0)
					socktype = SOCK_STREAM;
				else if (strcmp(sp->s_proto, "udp") == 0)
					socktype = SOCK_DGRAM;
			}
		}
	} else
		port = 0;

	/*
	 *
	 * Set up the port number
	 */
	if (ai->ai_family == AF_INET)
		((struct sockaddr_in *)ai->ai_addr)->sin_port = (unsigned short) port;
	else if (ai->ai_family == AF_INET6)
		((struct sockaddr_in6 *)ai->ai_addr)->sin6_port = (unsigned short) port;
	*res = ai;
	return (0);
}