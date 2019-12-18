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
typedef  int u_char ;
struct in6_addr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct in6_addr*,int /*<<< orphan*/ ,int) ; 

void
n2mask(struct in6_addr *mask, int n)
{
	static int	minimask[9] =
	    { 0x00, 0x80, 0xc0, 0xe0, 0xf0, 0xf8, 0xfc, 0xfe, 0xff };
	u_char		*p;

	memset(mask, 0, sizeof(struct in6_addr));
	p = (u_char *) mask;
	for (; n > 0; p++, n -= 8) {
		if (n >= 8)
			*p = 0xff;
		else
			*p = minimask[n];
	}
	return;
}