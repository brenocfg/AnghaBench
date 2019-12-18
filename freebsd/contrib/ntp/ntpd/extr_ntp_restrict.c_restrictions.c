#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct in6_addr {int dummy; } ;
typedef  int /*<<< orphan*/  sockaddr_u ;
struct TYPE_8__ {int ippeerlimit; int /*<<< orphan*/  rflags; int /*<<< orphan*/  count; } ;
typedef  TYPE_1__ restrict_u ;
struct TYPE_9__ {int ippeerlimit; int /*<<< orphan*/  rflags; } ;
typedef  TYPE_2__ r4addr ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (int,char*) ; 
 scalar_t__ IN6_IS_ADDR_MULTICAST (struct in6_addr*) ; 
 int /*<<< orphan*/  INSIST (int /*<<< orphan*/ ) ; 
 scalar_t__ IN_CLASSD (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_IPV4 (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_IPV6 (int /*<<< orphan*/ *) ; 
 struct in6_addr* PSOCK_ADDR6 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  REQUIRE (int) ; 
 int /*<<< orphan*/  RES_IGNORE ; 
 int /*<<< orphan*/  SRCADR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SRCPORT (int /*<<< orphan*/ *) ; 
 TYPE_1__* match_restrict4_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* match_restrict6_addr (struct in6_addr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  res_calls ; 
 int /*<<< orphan*/  res_found ; 
 int /*<<< orphan*/  res_not_found ; 
 TYPE_1__ restrict_def4 ; 
 TYPE_1__ restrict_def6 ; 
 int /*<<< orphan*/  stoa (int /*<<< orphan*/ *) ; 

void
restrictions(
	sockaddr_u *srcadr,
	r4addr *r4a
	)
{
	restrict_u *match;
	struct in6_addr *pin6;

	REQUIRE(NULL != r4a);

	res_calls++;
	r4a->rflags = RES_IGNORE;
	r4a->ippeerlimit = 0;

	DPRINTF(1, ("restrictions: looking up %s\n", stoa(srcadr)));

	/* IPv4 source address */
	if (IS_IPV4(srcadr)) {
		/*
		 * Ignore any packets with a multicast source address
		 * (this should be done early in the receive process,
		 * not later!)
		 */
		if (IN_CLASSD(SRCADR(srcadr))) {
			DPRINTF(1, ("restrictions: srcadr %s is multicast\n", stoa(srcadr)));
			r4a->ippeerlimit = 2;	/* XXX: we should use a better value */
			return;
		}

		match = match_restrict4_addr(SRCADR(srcadr),
					     SRCPORT(srcadr));

		INSIST(match != NULL);

		match->count++;
		/*
		 * res_not_found counts only use of the final default
		 * entry, not any "restrict default ntpport ...", which
		 * would be just before the final default.
		 */
		if (&restrict_def4 == match)
			res_not_found++;
		else
			res_found++;
		r4a->rflags = match->rflags;
		r4a->ippeerlimit = match->ippeerlimit;
	}

	/* IPv6 source address */
	if (IS_IPV6(srcadr)) {
		pin6 = PSOCK_ADDR6(srcadr);

		/*
		 * Ignore any packets with a multicast source address
		 * (this should be done early in the receive process,
		 * not later!)
		 */
		if (IN6_IS_ADDR_MULTICAST(pin6))
			return;

		match = match_restrict6_addr(pin6, SRCPORT(srcadr));
		INSIST(match != NULL);
		match->count++;
		if (&restrict_def6 == match)
			res_not_found++;
		else
			res_found++;
		r4a->rflags = match->rflags;
		r4a->ippeerlimit = match->ippeerlimit;
	}
	return;
}