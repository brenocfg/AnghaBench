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
struct sockaddr_in6 {int sin6_port; } ;
struct sockaddr_in {int sin_port; } ;
struct servent {int s_port; } ;
struct addrinfo {int ai_family; int ai_socktype; int ai_flags; int ai_protocol; scalar_t__ ai_addr; } ;

/* Variables and functions */
#define  AF_INET 139 
#define  AF_INET6 138 
#define  AF_LOCAL 137 
 int AI_NUMERICSERV ; 
#define  ANY 136 
 int EAI_NONAME ; 
 int EAI_SERVICE ; 
 int EAI_SOCKTYPE ; 
#define  IPPROTO_SCTP 135 
#define  IPPROTO_TCP 134 
#define  IPPROTO_UDP 133 
#define  IPPROTO_UDPLITE 132 
#define  SOCK_DGRAM 131 
#define  SOCK_RAW 130 
#define  SOCK_SEQPACKET 129 
#define  SOCK_STREAM 128 
 struct servent* getservbyname (char const*,char const*) ; 
 int htons (int) ; 
 int str2number (char const*,int*) ; 

__attribute__((used)) static int
get_port(struct addrinfo *ai, const char *servname, int matchonly)
{
	const char *proto;
	struct servent *sp;
	int port, error;
	int allownumeric;

	if (servname == NULL)
		return 0;
	switch (ai->ai_family) {
	case AF_LOCAL:
		/* AF_LOCAL ignores servname silently. */
		return (0);
	case AF_INET:
#ifdef AF_INET6
	case AF_INET6:
#endif
		break;
	default:
		return 0;
	}

	switch (ai->ai_socktype) {
	case SOCK_RAW:
		return EAI_SERVICE;
	case SOCK_DGRAM:
	case SOCK_STREAM:
	case SOCK_SEQPACKET:
		allownumeric = 1;
		break;
	case ANY:
		switch (ai->ai_family) {
		case AF_INET:
#ifdef AF_INET6
		case AF_INET6:
#endif
			allownumeric = 1;
			break;
		default:
			allownumeric = 0;
			break;
		}
		break;
	default:
		return EAI_SOCKTYPE;
	}

	error = str2number(servname, &port);
	if (error == 0) {
		if (!allownumeric)
			return EAI_SERVICE;
		if (port < 0 || port > 65535)
			return EAI_SERVICE;
		port = htons(port);
	} else {
		if (ai->ai_flags & AI_NUMERICSERV)
			return EAI_NONAME;

		switch (ai->ai_protocol) {
		case IPPROTO_UDP:
			proto = "udp";
			break;
		case IPPROTO_TCP:
			proto = "tcp";
			break;
		case IPPROTO_SCTP:
			proto = "sctp";
			break;
		case IPPROTO_UDPLITE:
			proto = "udplite";
			break;
		default:
			proto = NULL;
			break;
		}

		if ((sp = getservbyname(servname, proto)) == NULL)
			return EAI_SERVICE;
		port = sp->s_port;
	}

	if (!matchonly) {
		switch (ai->ai_family) {
		case AF_INET:
			((struct sockaddr_in *)(void *)
			    ai->ai_addr)->sin_port = port;
			break;
#ifdef INET6
		case AF_INET6:
			((struct sockaddr_in6 *)(void *)
			    ai->ai_addr)->sin6_port = port;
			break;
#endif
		}
	}

	return 0;
}