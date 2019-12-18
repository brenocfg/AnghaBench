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
struct cmsghdr {int cmsg_type; int /*<<< orphan*/  cmsg_len; int /*<<< orphan*/  cmsg_level; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMSG_LEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IPPROTO_IPV6 ; 
 int /*<<< orphan*/  is_ipv6_dstopts (int) ; 
 int /*<<< orphan*/  is_ipv6_hopopts (int) ; 

int
inet6_option_init(void *bp, struct cmsghdr **cmsgp, int type)
{
	struct cmsghdr *ch = (struct cmsghdr *)bp;

	/* argument validation */
	if (!is_ipv6_hopopts(type) && !is_ipv6_dstopts(type))
		return(-1);

	ch->cmsg_level = IPPROTO_IPV6;
	ch->cmsg_type = type;
	ch->cmsg_len = CMSG_LEN(0);

	*cmsgp = ch;
	return(0);
}