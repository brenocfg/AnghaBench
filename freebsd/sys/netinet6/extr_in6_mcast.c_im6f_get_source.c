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
struct in6_msource {int /*<<< orphan*/ * im6sl_st; int /*<<< orphan*/  im6s_addr; } ;
struct in6_mfilter {scalar_t__ im6f_nsrc; int /*<<< orphan*/  im6f_sources; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ENOSPC ; 
 int /*<<< orphan*/  MCAST_UNDEFINED ; 
 int /*<<< orphan*/  M_IN6MFILTER ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 struct ip6_msource* RB_FIND (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct ip6_msource*) ; 
 int /*<<< orphan*/  RB_INSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct ip6_msource*) ; 
 scalar_t__ in6_mcast_maxsocksrc ; 
 int /*<<< orphan*/  ip6_msource_tree ; 
 struct ip6_msource* malloc (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
im6f_get_source(struct in6_mfilter *imf, const struct sockaddr_in6 *psin,
    struct in6_msource **plims)
{
	struct ip6_msource	 find;
	struct ip6_msource	*ims, *nims;
	struct in6_msource	*lims;
	int			 error;

	error = 0;
	ims = NULL;
	lims = NULL;

	find.im6s_addr = psin->sin6_addr;
	ims = RB_FIND(ip6_msource_tree, &imf->im6f_sources, &find);
	lims = (struct in6_msource *)ims;
	if (lims == NULL) {
		if (imf->im6f_nsrc == in6_mcast_maxsocksrc)
			return (ENOSPC);
		nims = malloc(sizeof(struct in6_msource), M_IN6MFILTER,
		    M_NOWAIT | M_ZERO);
		if (nims == NULL)
			return (ENOMEM);
		lims = (struct in6_msource *)nims;
		lims->im6s_addr = find.im6s_addr;
		lims->im6sl_st[0] = MCAST_UNDEFINED;
		RB_INSERT(ip6_msource_tree, &imf->im6f_sources, nims);
		++imf->im6f_nsrc;
	}

	*plims = lims;

	return (error);
}