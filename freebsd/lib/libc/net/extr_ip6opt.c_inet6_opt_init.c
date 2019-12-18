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
struct ip6_ext {int ip6e_len; } ;
typedef  int socklen_t ;

/* Variables and functions */

int
inet6_opt_init(void *extbuf, socklen_t extlen)
{
	struct ip6_ext *ext = (struct ip6_ext *)extbuf;

	if (ext) {
		if (extlen <= 0 || (extlen % 8))
			return(-1);
		ext->ip6e_len = (extlen >> 3) - 1;
	}

	return(2);		/* sizeof the next and the length fields */
}