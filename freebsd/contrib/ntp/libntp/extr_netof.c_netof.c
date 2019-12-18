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
typedef  int /*<<< orphan*/  u_int32 ;
typedef  int /*<<< orphan*/  sockaddr_u ;

/* Variables and functions */
 int /*<<< orphan*/  AF (int /*<<< orphan*/ *) ; 
 int COUNTOF (int /*<<< orphan*/ *) ; 
 scalar_t__ IN_CLASSB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IN_CLASSB_NET ; 
 scalar_t__ IN_CLASSC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IN_CLASSC_NET ; 
 scalar_t__ IS_IPV4 (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_IPV6 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/ * NSRCADR6 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SET_ADDR4 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SRCADR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  msyslog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zero_mem (int /*<<< orphan*/ *,int) ; 

sockaddr_u *
netof(
	sockaddr_u *hostaddr
	)
{
	static sockaddr_u	netofbuf[8];
	static int		next_netofbuf;
	u_int32			netnum;
	sockaddr_u *		netaddr;

	netaddr = &netofbuf[next_netofbuf];
	next_netofbuf = (next_netofbuf + 1) % COUNTOF(netofbuf);

	memcpy(netaddr, hostaddr, sizeof(*netaddr));

	if (IS_IPV4(netaddr)) {
		netnum = SRCADR(netaddr);

		/*
		 * We live in a modern CIDR world where the basement nets, which
		 * used to be class A, are now probably associated with each
		 * host address. So, for class-A nets, all bits are significant.
		 */
		if (IN_CLASSC(netnum))
			netnum &= IN_CLASSC_NET;
		else if (IN_CLASSB(netnum))
			netnum &= IN_CLASSB_NET;

		SET_ADDR4(netaddr, netnum);

	} else if (IS_IPV6(netaddr))
		/* assume the typical /64 subnet size */
		zero_mem(&NSRCADR6(netaddr)[8], 8);
#ifdef DEBUG
	else {
		msyslog(LOG_ERR, "netof unknown AF %d", AF(netaddr));
		exit(1);
	}
#endif

	return netaddr;
}