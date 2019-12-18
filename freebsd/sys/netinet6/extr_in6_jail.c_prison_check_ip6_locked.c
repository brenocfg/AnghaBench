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
struct prison {int pr_ip6s; int /*<<< orphan*/ * pr_ip6; } ;
struct in6_addr {int dummy; } ;

/* Variables and functions */
 int EADDRNOTAVAIL ; 
 scalar_t__ IN6_ARE_ADDR_EQUAL (int /*<<< orphan*/ *,struct in6_addr const*) ; 
 int prison_qcmp_v6 (int /*<<< orphan*/ *,struct in6_addr const*) ; 

int
prison_check_ip6_locked(const struct prison *pr, const struct in6_addr *ia6)
{
	int i, a, z, d;

	/*
	 * Check the primary IP.
	 */
	if (IN6_ARE_ADDR_EQUAL(&pr->pr_ip6[0], ia6))
		return (0);

	/*
	 * All the other IPs are sorted so we can do a binary search.
	 */
	a = 0;
	z = pr->pr_ip6s - 2;
	while (a <= z) {
		i = (a + z) / 2;
		d = prison_qcmp_v6(&pr->pr_ip6[i+1], ia6);
		if (d > 0)
			z = i - 1;
		else if (d < 0)
			a = i + 1;
		else
			return (0);
	}

	return (EADDRNOTAVAIL);
}