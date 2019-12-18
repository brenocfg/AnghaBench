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
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
cdp_print_prefixes(netdissect_options *ndo,
		   const u_char * p, int l)
{
	if (l % 5)
		goto trunc;

	ND_PRINT((ndo, " IPv4 Prefixes (%d):", l / 5));

	while (l > 0) {
		ND_PRINT((ndo, " %u.%u.%u.%u/%u", p[0], p[1], p[2], p[3], p[4]));
		l -= 5;
		p += 5;
	}

	return 0;

trunc:
	return -1;
}