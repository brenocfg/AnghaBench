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
typedef  int /*<<< orphan*/  u_int32_t ;
struct sockaddr_in6 {int /*<<< orphan*/  sin6_scope_id; } ;
struct afd {int /*<<< orphan*/  a_scoped; } ;
struct addrinfo {scalar_t__ ai_family; scalar_t__ ai_addr; struct addrinfo* ai_next; } ;

/* Variables and functions */
 scalar_t__ AF_INET6 ; 
 int EAI_MEMORY ; 
 int EAI_NONAME ; 
 int /*<<< orphan*/  SCOPE_DELIMITER ; 
 int explore_numeric (struct addrinfo const*,char const*,char const*,struct addrinfo**,char const*) ; 
 struct afd* find_afd (scalar_t__) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  freeaddrinfo (struct addrinfo*) ; 
 int ip6_str2scopeid (char*,struct sockaddr_in6*,int /*<<< orphan*/ *) ; 
 char* strchr (char const*,int /*<<< orphan*/ ) ; 
 char* strdup (char const*) ; 

__attribute__((used)) static int
explore_numeric_scope(const struct addrinfo *pai, const char *hostname,
    const char *servname, struct addrinfo **res)
{
#if !defined(SCOPE_DELIMITER) || !defined(INET6)
	return explore_numeric(pai, hostname, servname, res, hostname);
#else
	const struct afd *afd;
	struct addrinfo *cur;
	int error;
	char *cp, *hostname2 = NULL, *scope, *addr;
	struct sockaddr_in6 *sin6;

	afd = find_afd(pai->ai_family);
	if (afd == NULL)
		return 0;

	if (!afd->a_scoped)
		return explore_numeric(pai, hostname, servname, res, hostname);

	cp = strchr(hostname, SCOPE_DELIMITER);
	if (cp == NULL)
		return explore_numeric(pai, hostname, servname, res, hostname);

	/*
	 * Handle special case of <scoped_address><delimiter><scope id>
	 */
	hostname2 = strdup(hostname);
	if (hostname2 == NULL)
		return EAI_MEMORY;
	/* terminate at the delimiter */
	hostname2[cp - hostname] = '\0';
	addr = hostname2;
	scope = cp + 1;

	error = explore_numeric(pai, addr, servname, res, hostname);
	if (error == 0) {
		u_int32_t scopeid;

		for (cur = *res; cur; cur = cur->ai_next) {
			if (cur->ai_family != AF_INET6)
				continue;
			sin6 = (struct sockaddr_in6 *)(void *)cur->ai_addr;
			if (ip6_str2scopeid(scope, sin6, &scopeid) == -1) {
				free(hostname2);
				freeaddrinfo(*res);
				*res = NULL;
				return(EAI_NONAME); /* XXX: is return OK? */
			}
			sin6->sin6_scope_id = scopeid;
		}
	}

	free(hostname2);

	if (error && *res) {
		freeaddrinfo(*res);
		*res = NULL;
	}
	return error;
#endif
}