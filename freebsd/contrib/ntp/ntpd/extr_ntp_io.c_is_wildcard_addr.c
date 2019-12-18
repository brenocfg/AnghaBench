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
 scalar_t__ IS_IPV4 (int /*<<< orphan*/  const*) ; 
 scalar_t__ IS_IPV6 (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  NSRCADR (int /*<<< orphan*/  const*) ; 
 scalar_t__ S_ADDR6_EQ (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  in6addr_any ; 

__attribute__((used)) static int
is_wildcard_addr(
	const sockaddr_u *psau
	)
{
	if (IS_IPV4(psau) && !NSRCADR(psau))
		return 1;

#ifdef INCLUDE_IPV6_SUPPORT
	if (IS_IPV6(psau) && S_ADDR6_EQ(psau, &in6addr_any))
		return 1;
#endif

	return 0;
}