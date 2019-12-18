#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct in6_addr {int dummy; } ;
struct ip6_msource {scalar_t__ im6s_stp; struct in6_addr im6s_addr; } ;
struct in6_multi {scalar_t__ in6m_nsrc; TYPE_1__* in6m_st; int /*<<< orphan*/  in6m_srcs; } ;
struct TYPE_2__ {int /*<<< orphan*/  iss_rec; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ENOSPC ; 
 int /*<<< orphan*/  IN6_MULTI_LIST_LOCK_ASSERT () ; 
 int /*<<< orphan*/  M_IP6MSOURCE ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 struct ip6_msource* RB_FIND (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct ip6_msource*) ; 
 int /*<<< orphan*/  RB_INSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct ip6_msource*) ; 
 scalar_t__ in6_mcast_maxgrpsrc ; 
 int /*<<< orphan*/  ip6_msource_tree ; 
 struct ip6_msource* malloc (int,int /*<<< orphan*/ ,int) ; 

int
in6m_record_source(struct in6_multi *inm, const struct in6_addr *addr)
{
	struct ip6_msource	 find;
	struct ip6_msource	*ims, *nims;

	IN6_MULTI_LIST_LOCK_ASSERT();

	find.im6s_addr = *addr;
	ims = RB_FIND(ip6_msource_tree, &inm->in6m_srcs, &find);
	if (ims && ims->im6s_stp)
		return (0);
	if (ims == NULL) {
		if (inm->in6m_nsrc == in6_mcast_maxgrpsrc)
			return (-ENOSPC);
		nims = malloc(sizeof(struct ip6_msource), M_IP6MSOURCE,
		    M_NOWAIT | M_ZERO);
		if (nims == NULL)
			return (-ENOMEM);
		nims->im6s_addr = find.im6s_addr;
		RB_INSERT(ip6_msource_tree, &inm->in6m_srcs, nims);
		++inm->in6m_nsrc;
		ims = nims;
	}

	/*
	 * Mark the source as recorded and update the recorded
	 * source count.
	 */
	++ims->im6s_stp;
	++inm->in6m_st[1].iss_rec;

	return (1);
}