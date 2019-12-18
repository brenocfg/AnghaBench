#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct addrinfo {int ai_addrlen; int /*<<< orphan*/ * ai_canonname; int /*<<< orphan*/  ai_addr; int /*<<< orphan*/  ai_flags; } ;
struct TYPE_6__ {int /*<<< orphan*/  sa; } ;
typedef  TYPE_1__ sockaddr_u ;

/* Variables and functions */
 int /*<<< orphan*/  AI_ADDRCONFIG ; 
 int /*<<< orphan*/  AI_CANONNAME ; 
 int /*<<< orphan*/  INSIST (int) ; 
 int /*<<< orphan*/  LENHOSTNAME ; 
 int /*<<< orphan*/  SOCKLEN (TYPE_1__*) ; 
 int /*<<< orphan*/  ZERO (struct addrinfo) ; 
 scalar_t__ decodenetnum (char const*,TYPE_1__*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  freeaddrinfo (struct addrinfo*) ; 
 scalar_t__ getaddrinfo (char const*,char*,struct addrinfo*,struct addrinfo**) ; 
 int /*<<< orphan*/  getnameinfo (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strlcpy (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
getnetnum(
	const char *hname,
	sockaddr_u *num,
	char *fullhost,
	int af
	)
{
	struct addrinfo hints, *ai = NULL;

	ZERO(hints);
	hints.ai_flags = AI_CANONNAME;
#ifdef AI_ADDRCONFIG
	hints.ai_flags |= AI_ADDRCONFIG;
#endif

	/*
	 * decodenetnum only works with addresses, but handles syntax
	 * that getaddrinfo doesn't:  [2001::1]:1234
	 */
	if (decodenetnum(hname, num)) {
		if (fullhost != NULL)
			getnameinfo(&num->sa, SOCKLEN(num), fullhost,
				    LENHOSTNAME, NULL, 0, 0);
		return 1;
	} else if (getaddrinfo(hname, "ntp", &hints, &ai) == 0) {
		INSIST(sizeof(*num) >= ai->ai_addrlen);
		memcpy(num, ai->ai_addr, ai->ai_addrlen);
		if (fullhost != NULL) {
			if (ai->ai_canonname != NULL)
				strlcpy(fullhost, ai->ai_canonname,
					LENHOSTNAME);
			else
				getnameinfo(&num->sa, SOCKLEN(num),
					    fullhost, LENHOSTNAME, NULL,
					    0, 0);
		}
		freeaddrinfo(ai);
		return 1;
	}
	fprintf(stderr, "***Can't find host %s\n", hname);

	return 0;
}