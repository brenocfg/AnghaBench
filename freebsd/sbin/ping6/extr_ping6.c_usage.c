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

/* Variables and functions */
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
usage(void)
{
	(void)fprintf(stderr,
#if defined(IPSEC) && !defined(IPSEC_POLICY_IPSEC)
	    "Z"
#endif
	    "usage: ping6 [-"
	    "aADd"
#if defined(IPSEC) && !defined(IPSEC_POLICY_IPSEC)
	    "E"
#endif
	    "fHnNoOq"
#ifdef IPV6_USE_MIN_MTU
	    "u"
#endif
	    "vyY] "
	    "[-b bufsiz] [-c count] [-e gateway]\n"
	    "             [-I interface] [-i wait] [-k addrtype] [-l preload] "
	    "[-m hoplimit]\n"
	    "             [-p pattern]"
#if defined(IPSEC) && defined(IPSEC_POLICY_IPSEC)
	    " [-P policy]"
#endif
	    " [-S sourceaddr] [-s packetsize]\n"
	    "             [-t timeout] [-W waittime] [hops ...] host\n");
	exit(1);
}