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
typedef  int /*<<< orphan*/  u_int8_t ;
struct ip6_ext {int ip6e_len; } ;
struct cmsghdr {scalar_t__ cmsg_level; scalar_t__ cmsg_len; int /*<<< orphan*/  cmsg_type; } ;

/* Variables and functions */
 scalar_t__ CMSG_DATA (struct cmsghdr const*) ; 
 scalar_t__ CMSG_SPACE (int) ; 
 scalar_t__ IPPROTO_IPV6 ; 
 int ip6optlen (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_ipv6_dstopts (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_ipv6_hopopts (int /*<<< orphan*/ ) ; 

int
inet6_option_next(const struct cmsghdr *cmsg, u_int8_t **tptrp)
{
	struct ip6_ext *ip6e;
	int hdrlen, optlen;
	u_int8_t *lim;

	if (cmsg->cmsg_level != IPPROTO_IPV6 ||
	    (!is_ipv6_hopopts(cmsg->cmsg_type) &&
	     !is_ipv6_dstopts(cmsg->cmsg_type)))
		return(-1);

	/* message length validation */
	if (cmsg->cmsg_len < CMSG_SPACE(sizeof(struct ip6_ext)))
		return(-1);
	ip6e = (struct ip6_ext *)CMSG_DATA(cmsg);
	hdrlen = (ip6e->ip6e_len + 1) << 3;
	if (cmsg->cmsg_len < CMSG_SPACE(hdrlen))
		return(-1);

	/*
	 * If the caller does not specify the starting point,
	 * simply return the 1st option.
	 * Otherwise, search the option list for the next option.
	 */
	lim = (u_int8_t *)ip6e + hdrlen;
	if (*tptrp == NULL)
		*tptrp = (u_int8_t *)(ip6e + 1);
	else {
		if ((optlen = ip6optlen(*tptrp, lim)) == 0)
			return(-1);

		*tptrp = *tptrp + optlen;
	}
	if (*tptrp >= lim) {	/* there is no option */
		*tptrp = NULL;
		return(-1);
	}
	/*
	 * Finally, checks if the next option is safely stored in the
	 * cmsg data.
	 */
	if (ip6optlen(*tptrp, lim) == 0)
		return(-1);
	else
		return(0);
}