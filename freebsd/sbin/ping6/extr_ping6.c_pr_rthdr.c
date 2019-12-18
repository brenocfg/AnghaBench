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
struct ip6_rthdr {int ip6r_nxt; int ip6r_len; int ip6r_type; int ip6r_segleft; } ;
struct in6_addr {int dummy; } ;
typedef  int /*<<< orphan*/  ntopbuf ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET6 ; 
 size_t CMSG_SPACE (int /*<<< orphan*/ ) ; 
 int INET6_ADDRSTRLEN ; 
 int /*<<< orphan*/  IPV6_RTHDR_TYPE_0 ; 
 struct in6_addr* inet6_rth_getaddr (void*,int) ; 
 int inet6_rth_segments (void*) ; 
 int inet6_rth_space (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  inet_ntop (int /*<<< orphan*/ ,struct in6_addr*,char*,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 
 int /*<<< orphan*/  warnx (char*,int,int) ; 

__attribute__((used)) static void
pr_rthdr(void *extbuf, size_t bufsize)
{
	struct in6_addr *in6;
	char ntopbuf[INET6_ADDRSTRLEN];
	struct ip6_rthdr *rh = (struct ip6_rthdr *)extbuf;
	int i, segments, origsegs, rthsize, size0, size1;

	/* print fixed part of the header */
	printf("nxt %u, len %u (%d bytes), type %u, ", rh->ip6r_nxt,
	    rh->ip6r_len, (rh->ip6r_len + 1) << 3, rh->ip6r_type);
	if ((segments = inet6_rth_segments(extbuf)) >= 0) {
		printf("%d segments, ", segments);
		printf("%d left\n", rh->ip6r_segleft);
	} else {
		printf("segments unknown, ");
		printf("%d left\n", rh->ip6r_segleft);
		return;
	}

	/*
	 * Bounds checking on the ancillary data buffer. When calculating
	 * the number of items to show keep in mind:
	 *	- The size of the cmsg structure
	 *	- The size of one segment (the size of a Type 0 routing header)
	 *	- When dividing add a fudge factor of one in case the
	 *	  dividend is not evenly divisible by the divisor
	 */
	rthsize = (rh->ip6r_len + 1) * 8;
	if (bufsize < (rthsize + CMSG_SPACE(0))) {
		origsegs = segments;
		size0 = inet6_rth_space(IPV6_RTHDR_TYPE_0, 0);
		size1 = inet6_rth_space(IPV6_RTHDR_TYPE_0, 1);
		segments -= (rthsize - (bufsize - CMSG_SPACE(0))) /
		    (size1 - size0) + 1;
		warnx("segments truncated, showing only %d (total=%d)",
		    segments, origsegs);
	}

	for (i = 0; i < segments; i++) {
		in6 = inet6_rth_getaddr(extbuf, i);
		if (in6 == NULL)
			printf("   [%d]<NULL>\n", i);
		else {
			if (!inet_ntop(AF_INET6, in6, ntopbuf,
			    sizeof(ntopbuf)))
				strlcpy(ntopbuf, "?", sizeof(ntopbuf));
			printf("   [%d]%s\n", i, ntopbuf);
		}
	}

	return;

}