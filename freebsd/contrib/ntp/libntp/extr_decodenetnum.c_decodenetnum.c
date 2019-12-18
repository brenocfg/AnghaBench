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
typedef  int /*<<< orphan*/  u_short ;
struct addrinfo {int ai_addrlen; int /*<<< orphan*/  ai_addr; int /*<<< orphan*/  ai_flags; } ;
typedef  struct addrinfo sockaddr_u ;
typedef  int /*<<< orphan*/  name ;

/* Variables and functions */
 int /*<<< orphan*/  INSIST (int) ; 
 int /*<<< orphan*/  NTP_PORT ; 
 int /*<<< orphan*/  REQUIRE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_PORT (struct addrinfo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZERO (struct addrinfo) ; 
 int /*<<< orphan*/  Z_AI_NUMERICHOST ; 
 int /*<<< orphan*/  freeaddrinfo (struct addrinfo*) ; 
 int getaddrinfo (char const*,char*,struct addrinfo*,struct addrinfo**) ; 
 int /*<<< orphan*/  memcpy (struct addrinfo*,int /*<<< orphan*/ ,int) ; 
 int sscanf (char const*,char*,int /*<<< orphan*/ *) ; 
 char* strchr (char const*,char) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,int) ; 
 int strlen (char const*) ; 

int
decodenetnum(
	const char *num,
	sockaddr_u *netnum
	)
{
	struct addrinfo hints, *ai = NULL;
	int err;
	u_short port;
	const char *cp;
	const char *port_str;
	char *pp;
	char *np;
	char name[80];

	REQUIRE(num != NULL);

	if (strlen(num) >= sizeof(name)) {
		return 0;
	}

	port_str = NULL;
	if ('[' != num[0]) {
		/*
		 * to distinguish IPv6 embedded colons from a port
		 * specification on an IPv4 address, assume all 
		 * legal IPv6 addresses have at least two colons.
		 */
		pp = strchr(num, ':');
		if (NULL == pp)
			cp = num;	/* no colons */
		else if (NULL != strchr(pp + 1, ':'))
			cp = num;	/* two or more colons */
		else {			/* one colon */
			strlcpy(name, num, sizeof(name));
			cp = name;
			pp = strchr(cp, ':');
			*pp = '\0';
			port_str = pp + 1;
		}
	} else {
		cp = num + 1;
		np = name; 
		while (*cp && ']' != *cp)
			*np++ = *cp++;
		*np = 0;
		if (']' == cp[0] && ':' == cp[1] && '\0' != cp[2])
			port_str = &cp[2];
		cp = name; 
	}
	ZERO(hints);
	hints.ai_flags = Z_AI_NUMERICHOST;
	err = getaddrinfo(cp, "ntp", &hints, &ai);
	if (err != 0)
		return 0;
	INSIST(ai->ai_addrlen <= sizeof(*netnum));
	ZERO(*netnum);
	memcpy(netnum, ai->ai_addr, ai->ai_addrlen);
	freeaddrinfo(ai);
	if (NULL == port_str || 1 != sscanf(port_str, "%hu", &port))
		port = NTP_PORT;
	SET_PORT(netnum, port);
	return 1;
}