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
struct sockaddr_in6 {int /*<<< orphan*/  sin6_addr; } ;
struct ip6_msource {int /*<<< orphan*/  im6s_addr; } ;
struct in6_msource {int /*<<< orphan*/ * im6sl_st; } ;
struct in6_mfilter {int /*<<< orphan*/  im6f_sources; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  MCAST_UNDEFINED ; 
 struct ip6_msource* RB_FIND (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct ip6_msource*) ; 
 int /*<<< orphan*/  ip6_msource_tree ; 

__attribute__((used)) static int
im6f_prune(struct in6_mfilter *imf, const struct sockaddr_in6 *psin)
{
	struct ip6_msource	 find;
	struct ip6_msource	*ims;
	struct in6_msource	*lims;

	find.im6s_addr = psin->sin6_addr;
	ims = RB_FIND(ip6_msource_tree, &imf->im6f_sources, &find);
	if (ims == NULL)
		return (ENOENT);
	lims = (struct in6_msource *)ims;
	lims->im6sl_st[1] = MCAST_UNDEFINED;
	return (0);
}