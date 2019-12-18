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
typedef  int /*<<< orphan*/  sockaddr_u ;

/* Variables and functions */
 scalar_t__ ISBADADR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ISREFCLOCKADR (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_IPV6 (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_MCAST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int T_Manycastclient ; 
 int T_Peer ; 
 int T_Pool ; 
 int T_Server ; 
 int /*<<< orphan*/  ipv6_works ; 
 int /*<<< orphan*/  msyslog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stoa (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
is_sane_resolved_address(
	sockaddr_u *	peeraddr,
	int		hmode
	)
{
	if (!ISREFCLOCKADR(peeraddr) && ISBADADR(peeraddr)) {
		msyslog(LOG_ERR,
			"attempt to configure invalid address %s",
			stoa(peeraddr));
		return 0;
	}
	/*
	 * Shouldn't be able to specify multicast
	 * address for server/peer!
	 * and unicast address for manycastclient!
	 */
	if ((T_Server == hmode || T_Peer == hmode || T_Pool == hmode)
	    && IS_MCAST(peeraddr)) {
		msyslog(LOG_ERR,
			"attempt to configure invalid address %s",
			stoa(peeraddr));
		return 0;
	}
	if (T_Manycastclient == hmode && !IS_MCAST(peeraddr)) {
		msyslog(LOG_ERR,
			"attempt to configure invalid address %s",
			stoa(peeraddr));
		return 0;
	}

	if (IS_IPV6(peeraddr) && !ipv6_works)
		return 0;

	/* Ok, all tests succeeded, now we can return 1 */
	return 1;
}