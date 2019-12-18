#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sockaddr_storage {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in6 {short sin6_family; TYPE_1__ sin6_addr; } ;
struct sockaddr_in {short sin_family; TYPE_1__ sin_addr; } ;
struct sockaddr {void* sa_family; } ;
struct hostent {void* h_addrtype; int /*<<< orphan*/  h_name; int /*<<< orphan*/  h_length; int /*<<< orphan*/  h_addr; } ;
struct addrinfo {void* ai_family; int ai_addrlen; int ai_flags; int /*<<< orphan*/  ai_canonname; TYPE_3__* ai_addr; } ;
struct TYPE_6__ {int sa_len; void* sa_family; } ;

/* Variables and functions */
 void* AF_INET ; 
 void* AF_INET6 ; 
 int AI_CANONNAME ; 
 int AI_NUMERICHOST ; 
 int DNSlookup_name (char const*,void*,struct hostent**) ; 
 int EAI_AGAIN ; 
 int EAI_MEMORY ; 
 int EAI_NONAME ; 
 int /*<<< orphan*/  INADDR_ANY ; 
 int SOCKLEN (TYPE_3__*) ; 
 int TRY_AGAIN ; 
 TYPE_3__* calloc (int,int) ; 
 int /*<<< orphan*/  estrdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int inet_pton (void*,char const*,TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * strchr (char const*,char) ; 

__attribute__((used)) static int
do_nodename(
	const char *nodename,
	struct addrinfo *ai,
	const struct addrinfo *hints)
{
	struct hostent *hp = NULL;
	struct sockaddr_in *sockin;
	struct sockaddr_in6 *sockin6;
	int errval;

	ai->ai_addr = calloc(sizeof(struct sockaddr_storage), 1);
	if (ai->ai_addr == NULL)
		return (EAI_MEMORY);

	/*
	 * For an empty node name just use the wildcard.
	 * NOTE: We need to assume that the address family is
	 * set elsewhere so that we can set the appropriate wildcard
	 */
	if (nodename == NULL) {
		if (ai->ai_family == AF_INET)
		{
			ai->ai_addrlen = sizeof(struct sockaddr_in);
			sockin = (struct sockaddr_in *)ai->ai_addr;
			sockin->sin_family = (short) ai->ai_family;
			sockin->sin_addr.s_addr = htonl(INADDR_ANY);
		}
		else
		{
			ai->ai_addrlen = sizeof(struct sockaddr_in6);
			sockin6 = (struct sockaddr_in6 *)ai->ai_addr;
			sockin6->sin6_family = (short) ai->ai_family;
			/*
			 * we have already zeroed out the address
			 * so we don't actually need to do this
			 * This assignment is causing problems so
			 * we don't do what this would do.
			 sockin6->sin6_addr = in6addr_any;
			 */
		}
#ifdef ISC_PLATFORM_HAVESALEN
		ai->ai_addr->sa_len = SOCKLEN(ai->ai_addr);
#endif

		return (0);
	}

	/*
	 * See if we have an IPv6 address
	 */
	if(strchr(nodename, ':') != NULL) {
		if (inet_pton(AF_INET6, nodename,
		    &((struct sockaddr_in6 *)ai->ai_addr)->sin6_addr) == 1) {
			((struct sockaddr_in6 *)ai->ai_addr)->sin6_family = AF_INET6;
			ai->ai_family = AF_INET6;
			ai->ai_addrlen = sizeof(struct sockaddr_in6);
			return (0);
		}
	}

	/*
	 * See if we have an IPv4 address
	 */
	if (inet_pton(AF_INET, nodename,
	    &((struct sockaddr_in *)ai->ai_addr)->sin_addr) == 1) {
		((struct sockaddr *)ai->ai_addr)->sa_family = AF_INET;
		ai->ai_family = AF_INET;
		ai->ai_addrlen = sizeof(struct sockaddr_in);
		return (0);
	}

	/*
	 * If the numeric host flag is set, don't attempt resolution
	 */
	if (hints != NULL && (hints->ai_flags & AI_NUMERICHOST))
		return (EAI_NONAME);

	/*
	 * Look for a name
	 */

	errval = DNSlookup_name(nodename, AF_INET, &hp);

	if (hp == NULL) {
		if (errval == TRY_AGAIN || errval == EAI_AGAIN)
			return (EAI_AGAIN);
		else if (errval == EAI_NONAME) {
			if (inet_pton(AF_INET, nodename,
			    &((struct sockaddr_in *)ai->ai_addr)->sin_addr) == 1) {
				((struct sockaddr *)ai->ai_addr)->sa_family = AF_INET;
				ai->ai_family = AF_INET;
				ai->ai_addrlen = sizeof(struct sockaddr_in);
				return (0);
			}
			return (errval);
		}
		else
		{
			return (errval);
		}
	}
	ai->ai_family = hp->h_addrtype;
	ai->ai_addrlen = sizeof(struct sockaddr);
	sockin = (struct sockaddr_in *)ai->ai_addr;
	memcpy(&sockin->sin_addr, hp->h_addr, hp->h_length);
	ai->ai_addr->sa_family = hp->h_addrtype;
#ifdef ISC_PLATFORM_HAVESALEN
	ai->ai_addr->sa_len = sizeof(struct sockaddr);
#endif
	if (hints != NULL && (hints->ai_flags & AI_CANONNAME))
		ai->ai_canonname = estrdup(hp->h_name);
	return (0);
}