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
struct sockaddr_in6 {int /*<<< orphan*/  sin6_addr; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_addr; } ;
struct sockaddr {int sa_family; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int FALSE ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
nlm_compare_addr(const struct sockaddr *a, const struct sockaddr *b)
{
	const struct sockaddr_in *a4, *b4;
#ifdef INET6
	const struct sockaddr_in6 *a6, *b6;
#endif

	if (a->sa_family != b->sa_family)
		return (FALSE);

	switch (a->sa_family) {
	case AF_INET:
		a4 = (const struct sockaddr_in *) a;
		b4 = (const struct sockaddr_in *) b;
		return !memcmp(&a4->sin_addr, &b4->sin_addr,
		    sizeof(a4->sin_addr));
#ifdef INET6
	case AF_INET6:
		a6 = (const struct sockaddr_in6 *) a;
		b6 = (const struct sockaddr_in6 *) b;
		return !memcmp(&a6->sin6_addr, &b6->sin6_addr,
		    sizeof(a6->sin6_addr));
#endif
	}

	return (0);
}