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
typedef  int /*<<< orphan*/  uint8_t ;
struct sockaddr_in6 {int /*<<< orphan*/  sin6_addr; } ;
struct ip6_msource {int dummy; } ;
struct in6_msource {int /*<<< orphan*/ * im6sl_st; int /*<<< orphan*/  im6s_addr; } ;
struct in6_mfilter {int /*<<< orphan*/  im6f_nsrc; int /*<<< orphan*/  im6f_sources; } ;

/* Variables and functions */
 int /*<<< orphan*/  MCAST_UNDEFINED ; 
 int /*<<< orphan*/  M_IN6MFILTER ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  RB_INSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct ip6_msource*) ; 
 int /*<<< orphan*/  ip6_msource_tree ; 
 struct ip6_msource* malloc (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct in6_msource *
im6f_graft(struct in6_mfilter *imf, const uint8_t st1,
    const struct sockaddr_in6 *psin)
{
	struct ip6_msource	*nims;
	struct in6_msource	*lims;

	nims = malloc(sizeof(struct in6_msource), M_IN6MFILTER,
	    M_NOWAIT | M_ZERO);
	if (nims == NULL)
		return (NULL);
	lims = (struct in6_msource *)nims;
	lims->im6s_addr = psin->sin6_addr;
	lims->im6sl_st[0] = MCAST_UNDEFINED;
	lims->im6sl_st[1] = st1;
	RB_INSERT(ip6_msource_tree, &imf->im6f_sources, nims);
	++imf->im6f_nsrc;

	return (lims);
}