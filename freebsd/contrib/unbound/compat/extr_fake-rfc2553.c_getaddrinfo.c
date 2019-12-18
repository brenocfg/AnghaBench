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
typedef  int /*<<< orphan*/  u_long ;
struct servent {long s_port; } ;
struct in_addr {int /*<<< orphan*/  s_addr; } ;
struct hostent {scalar_t__* h_addr_list; scalar_t__* h_name; } ;
struct addrinfo {int ai_flags; struct addrinfo* ai_next; } ;

/* Variables and functions */
 int AI_NUMERICHOST ; 
 int AI_PASSIVE ; 
 int EAI_MEMORY ; 
 int EAI_NODATA ; 
 int EAI_NONAME ; 
 int /*<<< orphan*/  freeaddrinfo (struct addrinfo*) ; 
 struct hostent* gethostbyname (char const*) ; 
 struct servent* getservbyname (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  htonl (int) ; 
 long htons (long) ; 
 scalar_t__ inet_aton (char const*,struct in_addr*) ; 
 struct addrinfo* malloc_ai (long,int /*<<< orphan*/ ,struct addrinfo const*) ; 
 long strtol (char const*,char**,int) ; 

int
getaddrinfo(const char *hostname, const char *servname, 
    const struct addrinfo *hints, struct addrinfo **res)
{
	struct hostent *hp;
	struct servent *sp;
	struct in_addr in;
	int i;
	long int port;
	u_long addr;

	port = 0;
	if (servname != NULL) {
		char *cp;

		port = strtol(servname, &cp, 10);
		if (port > 0 && port <= 65535 && *cp == '\0')
			port = htons(port);
		else if ((sp = getservbyname(servname, NULL)) != NULL)
			port = sp->s_port;
		else
			port = 0;
	}

	if (hints && hints->ai_flags & AI_PASSIVE) {
		addr = htonl(0x00000000);
		if (hostname && inet_aton(hostname, &in) != 0)
			addr = in.s_addr;
		*res = malloc_ai(port, addr, hints);
		if (*res == NULL) 
			return (EAI_MEMORY);
		return (0);
	}
		
	if (!hostname) {
		*res = malloc_ai(port, htonl(0x7f000001), hints);
		if (*res == NULL) 
			return (EAI_MEMORY);
		return (0);
	}
	
	if (inet_aton(hostname, &in)) {
		*res = malloc_ai(port, in.s_addr, hints);
		if (*res == NULL) 
			return (EAI_MEMORY);
		return (0);
	}
	
	/* Don't try DNS if AI_NUMERICHOST is set */
	if (hints && hints->ai_flags & AI_NUMERICHOST)
		return (EAI_NONAME);
	
	hp = gethostbyname(hostname);
	if (hp && hp->h_name && hp->h_name[0] && hp->h_addr_list[0]) {
		struct addrinfo *cur, *prev;

		cur = prev = *res = NULL;
		for (i = 0; hp->h_addr_list[i]; i++) {
			struct in_addr *in = (struct in_addr *)hp->h_addr_list[i];

			cur = malloc_ai(port, in->s_addr, hints);
			if (cur == NULL) {
				if (*res != NULL)
					freeaddrinfo(*res);
				return (EAI_MEMORY);
			}
			if (prev)
				prev->ai_next = cur;
			else
				*res = cur;

			prev = cur;
		}
		return (0);
	}
	
	return (EAI_NODATA);
}