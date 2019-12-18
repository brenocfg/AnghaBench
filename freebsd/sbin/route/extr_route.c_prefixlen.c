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
typedef  int u_char ;
struct sockaddr_in6 {int sin6_family; int sin6_len; int /*<<< orphan*/  sin6_addr; } ;
struct sockaddr_in {int sin_family; int sin_len; int /*<<< orphan*/  sin_addr; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int /*<<< orphan*/  EX_OSERR ; 
 int /*<<< orphan*/  EX_USAGE ; 
 size_t RTAX_NETMASK ; 
 int /*<<< orphan*/  RTA_NETMASK ; 
 int af ; 
 int atoi (char const*) ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  memset (void*,int,int) ; 
 int /*<<< orphan*/  rtm_addrs ; 
 int /*<<< orphan*/ * so ; 

__attribute__((used)) static int
prefixlen(const char *str)
{
	int len = atoi(str), q, r;
	int max;
	char *p;

	rtm_addrs |= RTA_NETMASK;
	switch (af) {
#ifdef INET6
	case AF_INET6:
	{
		struct sockaddr_in6 *sin6 =
		    (struct sockaddr_in6 *)&so[RTAX_NETMASK];

		max = 128;
		p = (char *)&sin6->sin6_addr;
		sin6->sin6_family = AF_INET6;
		sin6->sin6_len = sizeof(*sin6);
		break;
	}
#endif
#ifdef INET
	case AF_INET:
	{
		struct sockaddr_in *sin =
		    (struct sockaddr_in *)&so[RTAX_NETMASK];

		max = 32;
		p = (char *)&sin->sin_addr;
		sin->sin_family = AF_INET;
		sin->sin_len = sizeof(*sin);
		break;
	}
#endif
	default:
		errx(EX_OSERR, "prefixlen not supported in this af");
	}

	if (len < 0 || max < len)
		errx(EX_USAGE, "%s: invalid prefixlen", str);

	q = len >> 3;
	r = len & 7;
	memset((void *)p, 0, max / 8);
	if (q > 0)
		memset((void *)p, 0xff, q);
	if (r > 0)
		*((u_char *)p + q) = (0xff00 >> r) & 0xff;
	if (len == max)
		return (-1);
	else
		return (len);
}