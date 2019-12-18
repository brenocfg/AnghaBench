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
struct in6_addr {int /*<<< orphan*/ * s6_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/ * plent ; 

__attribute__((used)) static void
applyplen(struct in6_addr *ia, int plen)
{
	u_char	*p;
	int	i;

	p = ia->s6_addr;
	for (i = 0; i < 16; i++) {
		if (plen <= 0)
			*p = 0;
		else if (plen < 8)
			*p &= plent[plen];
		p++, plen -= 8;
	}
}