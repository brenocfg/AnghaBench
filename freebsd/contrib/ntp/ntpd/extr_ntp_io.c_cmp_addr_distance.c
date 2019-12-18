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
 scalar_t__ AF (int /*<<< orphan*/  const*) ; 
 scalar_t__ IS_IPV4 (int /*<<< orphan*/  const*) ; 
 scalar_t__* NSRCADR6 (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  REQUIRE (int) ; 
 scalar_t__ SRCADR (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int
cmp_addr_distance(
	const sockaddr_u *	d1,
	const sockaddr_u *	d2
	)
{
	int	i;

	REQUIRE(AF(d1) == AF(d2));

	if (IS_IPV4(d1)) {
		if (SRCADR(d1) < SRCADR(d2))
			return -1;
		else if (SRCADR(d1) == SRCADR(d2))
			return 0;
		else
			return 1;
	}

	for (i = 0; i < (int)sizeof(NSRCADR6(d1)); i++) {
		if (NSRCADR6(d1)[i] < NSRCADR6(d2)[i])
			return -1;
		else if (NSRCADR6(d1)[i] > NSRCADR6(d2)[i])
			return 1;
	}

	return 0;
}