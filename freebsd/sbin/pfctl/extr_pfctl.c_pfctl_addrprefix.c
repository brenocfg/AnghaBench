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
typedef  int u_char ;
struct addrinfo {int ai_family; int /*<<< orphan*/  s_addr; int /*<<< orphan*/  ai_flags; } ;
struct pf_addr {struct addrinfo v6; struct addrinfo v4; } ;
typedef  int /*<<< orphan*/  hints ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int /*<<< orphan*/  AI_NUMERICHOST ; 
 int /*<<< orphan*/  bzero (struct addrinfo*,int) ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 int /*<<< orphan*/  freeaddrinfo (struct addrinfo*) ; 
 int /*<<< orphan*/  gai_strerror (int) ; 
 int getaddrinfo (char*,int /*<<< orphan*/ *,struct addrinfo*,struct addrinfo**) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (void*,int,int) ; 
 char* strchr (char*,char) ; 
 int strtonum (char*,int /*<<< orphan*/ ,int,char const**) ; 

void
pfctl_addrprefix(char *addr, struct pf_addr *mask)
{
	char *p;
	const char *errstr;
	int prefix, ret_ga, q, r;
	struct addrinfo hints, *res;

	if ((p = strchr(addr, '/')) == NULL)
		return;

	*p++ = '\0';
	prefix = strtonum(p, 0, 128, &errstr);
	if (errstr)
		errx(1, "prefix is %s: %s", errstr, p);

	bzero(&hints, sizeof(hints));
	/* prefix only with numeric addresses */
	hints.ai_flags |= AI_NUMERICHOST;

	if ((ret_ga = getaddrinfo(addr, NULL, &hints, &res))) {
		errx(1, "getaddrinfo: %s", gai_strerror(ret_ga));
		/* NOTREACHED */
	}

	if (res->ai_family == AF_INET && prefix > 32)
		errx(1, "prefix too long for AF_INET");
	else if (res->ai_family == AF_INET6 && prefix > 128)
		errx(1, "prefix too long for AF_INET6");

	q = prefix >> 3;
	r = prefix & 7;
	switch (res->ai_family) {
	case AF_INET:
		bzero(&mask->v4, sizeof(mask->v4));
		mask->v4.s_addr = htonl((u_int32_t)
		    (0xffffffffffULL << (32 - prefix)));
		break;
	case AF_INET6:
		bzero(&mask->v6, sizeof(mask->v6));
		if (q > 0)
			memset((void *)&mask->v6, 0xff, q);
		if (r > 0)
			*((u_char *)&mask->v6 + q) =
			    (0xff00 >> r) & 0xff;
		break;
	}
	freeaddrinfo(res);
}