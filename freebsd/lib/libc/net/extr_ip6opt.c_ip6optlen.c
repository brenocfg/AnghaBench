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
typedef  scalar_t__ u_int8_t ;

/* Variables and functions */
 scalar_t__ IP6OPT_PAD1 ; 

__attribute__((used)) static int
ip6optlen(u_int8_t *opt, u_int8_t *lim)
{
	int optlen;

	if (*opt == IP6OPT_PAD1)
		optlen = 1;
	else {
		/* is there enough space to store type and len? */
		if (opt + 2 > lim)
			return(0);
		optlen = *(opt + 1) + 2;
	}
	if (opt + optlen <= lim)
		return(optlen);

	return(0);
}