#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * ro_rt; } ;
struct TYPE_5__ {int /*<<< orphan*/ * ip6po_rhi_rthdr; } ;
struct TYPE_4__ {int /*<<< orphan*/ * ro_rt; } ;
struct ip6_pktopts {int ip6po_hlim; int ip6po_tclass; int /*<<< orphan*/ * ip6po_dest2; TYPE_3__ ip6po_route; TYPE_2__ ip6po_rhinfo; int /*<<< orphan*/ * ip6po_dest1; int /*<<< orphan*/ * ip6po_hbh; int /*<<< orphan*/ * ip6po_nexthop; TYPE_1__ ip6po_nextroute; int /*<<< orphan*/ * ip6po_pktinfo; } ;

/* Variables and functions */
 int IPV6_DSTOPTS ; 
 int IPV6_HOPLIMIT ; 
 int IPV6_HOPOPTS ; 
 int IPV6_NEXTHOP ; 
 int IPV6_PKTINFO ; 
 int IPV6_RTHDR ; 
 int IPV6_RTHDRDSTOPTS ; 
 int IPV6_TCLASS ; 
 int /*<<< orphan*/  M_IP6OPT ; 
 int /*<<< orphan*/  RTFREE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
ip6_clearpktopts(struct ip6_pktopts *pktopt, int optname)
{
	if (pktopt == NULL)
		return;

	if (optname == -1 || optname == IPV6_PKTINFO) {
		if (pktopt->ip6po_pktinfo)
			free(pktopt->ip6po_pktinfo, M_IP6OPT);
		pktopt->ip6po_pktinfo = NULL;
	}
	if (optname == -1 || optname == IPV6_HOPLIMIT)
		pktopt->ip6po_hlim = -1;
	if (optname == -1 || optname == IPV6_TCLASS)
		pktopt->ip6po_tclass = -1;
	if (optname == -1 || optname == IPV6_NEXTHOP) {
		if (pktopt->ip6po_nextroute.ro_rt) {
			RTFREE(pktopt->ip6po_nextroute.ro_rt);
			pktopt->ip6po_nextroute.ro_rt = NULL;
		}
		if (pktopt->ip6po_nexthop)
			free(pktopt->ip6po_nexthop, M_IP6OPT);
		pktopt->ip6po_nexthop = NULL;
	}
	if (optname == -1 || optname == IPV6_HOPOPTS) {
		if (pktopt->ip6po_hbh)
			free(pktopt->ip6po_hbh, M_IP6OPT);
		pktopt->ip6po_hbh = NULL;
	}
	if (optname == -1 || optname == IPV6_RTHDRDSTOPTS) {
		if (pktopt->ip6po_dest1)
			free(pktopt->ip6po_dest1, M_IP6OPT);
		pktopt->ip6po_dest1 = NULL;
	}
	if (optname == -1 || optname == IPV6_RTHDR) {
		if (pktopt->ip6po_rhinfo.ip6po_rhi_rthdr)
			free(pktopt->ip6po_rhinfo.ip6po_rhi_rthdr, M_IP6OPT);
		pktopt->ip6po_rhinfo.ip6po_rhi_rthdr = NULL;
		if (pktopt->ip6po_route.ro_rt) {
			RTFREE(pktopt->ip6po_route.ro_rt);
			pktopt->ip6po_route.ro_rt = NULL;
		}
	}
	if (optname == -1 || optname == IPV6_DSTOPTS) {
		if (pktopt->ip6po_dest2)
			free(pktopt->ip6po_dest2, M_IP6OPT);
		pktopt->ip6po_dest2 = NULL;
	}
}