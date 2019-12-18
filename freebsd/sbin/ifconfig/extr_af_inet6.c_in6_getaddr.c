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
struct sockaddr_in6 {int sin6_len; scalar_t__ sin6_family; int /*<<< orphan*/  sin6_addr; } ;
struct addrinfo {int /*<<< orphan*/  ai_addrlen; int /*<<< orphan*/  ai_addr; scalar_t__ ai_family; } ;

/* Variables and functions */
 int ADDR ; 
 scalar_t__ AF_INET6 ; 
 int MASK ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,struct sockaddr_in6*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (struct addrinfo*,int) ; 
 int /*<<< orphan*/  errx (int,char*,char const*) ; 
 int explicit_prefix ; 
 int /*<<< orphan*/  freeaddrinfo (struct addrinfo*) ; 
 int getaddrinfo (char const*,int /*<<< orphan*/ *,struct addrinfo*,struct addrinfo**) ; 
 int /*<<< orphan*/  in6_getprefix (char*,int) ; 
 int inet_pton (scalar_t__,char const*,int /*<<< orphan*/ *) ; 
 int newaddr ; 
 struct sockaddr_in6** sin6tab ; 
 char* strrchr (char const*,char) ; 

__attribute__((used)) static void
in6_getaddr(const char *s, int which)
{
	struct sockaddr_in6 *sin = sin6tab[which];
	struct addrinfo hints, *res;
	int error = -1;

	newaddr &= 1;

	sin->sin6_len = sizeof(*sin);
	if (which != MASK)
		sin->sin6_family = AF_INET6;

	if (which == ADDR) {
		char *p = NULL;
		if((p = strrchr(s, '/')) != NULL) {
			*p = '\0';
			in6_getprefix(p + 1, MASK);
			explicit_prefix = 1;
		}
	}

	if (sin->sin6_family == AF_INET6) {
		bzero(&hints, sizeof(struct addrinfo));
		hints.ai_family = AF_INET6;
		error = getaddrinfo(s, NULL, &hints, &res);
		if (error != 0) {
			if (inet_pton(AF_INET6, s, &sin->sin6_addr) != 1)
				errx(1, "%s: bad value", s);
		} else {
			bcopy(res->ai_addr, sin, res->ai_addrlen);
			freeaddrinfo(res);
		}
	}
}