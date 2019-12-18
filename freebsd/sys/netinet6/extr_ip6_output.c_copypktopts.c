#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ip6_pktopts {TYPE_1__* ip6po_nexthop; int /*<<< orphan*/ * ip6po_pktinfo; int /*<<< orphan*/  ip6po_prefer_tempaddr; int /*<<< orphan*/  ip6po_minmtu; int /*<<< orphan*/  ip6po_flags; int /*<<< orphan*/  ip6po_tclass; int /*<<< orphan*/  ip6po_hlim; } ;
struct TYPE_3__ {int sa_len; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOBUFS ; 
 int /*<<< orphan*/  M_IP6OPT ; 
 int /*<<< orphan*/  PKTOPT_EXTHDRCPY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcopy (TYPE_1__*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  ip6_clearpktopts (struct ip6_pktopts*,int) ; 
 int /*<<< orphan*/  ip6po_dest1 ; 
 int /*<<< orphan*/  ip6po_dest2 ; 
 int /*<<< orphan*/  ip6po_hbh ; 
 int /*<<< orphan*/  ip6po_rthdr ; 
 void* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static int
copypktopts(struct ip6_pktopts *dst, struct ip6_pktopts *src, int canwait)
{
	if (dst == NULL || src == NULL)  {
		printf("ip6_clearpktopts: invalid argument\n");
		return (EINVAL);
	}

	dst->ip6po_hlim = src->ip6po_hlim;
	dst->ip6po_tclass = src->ip6po_tclass;
	dst->ip6po_flags = src->ip6po_flags;
	dst->ip6po_minmtu = src->ip6po_minmtu;
	dst->ip6po_prefer_tempaddr = src->ip6po_prefer_tempaddr;
	if (src->ip6po_pktinfo) {
		dst->ip6po_pktinfo = malloc(sizeof(*dst->ip6po_pktinfo),
		    M_IP6OPT, canwait);
		if (dst->ip6po_pktinfo == NULL)
			goto bad;
		*dst->ip6po_pktinfo = *src->ip6po_pktinfo;
	}
	if (src->ip6po_nexthop) {
		dst->ip6po_nexthop = malloc(src->ip6po_nexthop->sa_len,
		    M_IP6OPT, canwait);
		if (dst->ip6po_nexthop == NULL)
			goto bad;
		bcopy(src->ip6po_nexthop, dst->ip6po_nexthop,
		    src->ip6po_nexthop->sa_len);
	}
	PKTOPT_EXTHDRCPY(ip6po_hbh);
	PKTOPT_EXTHDRCPY(ip6po_dest1);
	PKTOPT_EXTHDRCPY(ip6po_dest2);
	PKTOPT_EXTHDRCPY(ip6po_rthdr); /* not copy the cached route */
	return (0);

  bad:
	ip6_clearpktopts(dst, -1);
	return (ENOBUFS);
}