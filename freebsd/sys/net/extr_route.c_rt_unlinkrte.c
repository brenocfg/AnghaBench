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
struct sockaddr {int dummy; } ;
struct rtentry {int rt_flags; struct sockaddr* rt_gateway; } ;
struct rt_addrinfo {int rti_flags; scalar_t__ (* rti_filter ) (struct rtentry*,int /*<<< orphan*/ ) ;struct sockaddr** rti_info; int /*<<< orphan*/  rti_filterdata; } ;
struct rib_head {int /*<<< orphan*/  head; struct radix_node* (* rnh_deladdr ) (struct sockaddr*,struct sockaddr*,int /*<<< orphan*/ *) ;scalar_t__ (* rnh_lookup ) (struct sockaddr*,struct sockaddr*,int /*<<< orphan*/ *) ;} ;
struct radix_node {int rn_flags; } ;

/* Variables and functions */
 int EADDRINUSE ; 
 int ENOENT ; 
 int ESRCH ; 
 int RNF_ACTIVE ; 
 int RNF_ROOT ; 
 struct rtentry* RNTORT (struct radix_node*) ; 
 size_t RTAX_DST ; 
 size_t RTAX_GATEWAY ; 
 size_t RTAX_NETMASK ; 
 int RTF_PINNED ; 
 int RTF_UP ; 
 int /*<<< orphan*/  RT_ADDREF (struct rtentry*) ; 
 int /*<<< orphan*/  RT_LOCK (struct rtentry*) ; 
 int /*<<< orphan*/  panic (char*) ; 
 scalar_t__ rt_mpath_capable (struct rib_head*) ; 
 struct radix_node* rt_mpath_unlink (struct rib_head*,struct rt_addrinfo*,struct rtentry*,int*) ; 
 scalar_t__ stub1 (struct sockaddr*,struct sockaddr*,int /*<<< orphan*/ *) ; 
 scalar_t__ stub2 (struct rtentry*,int /*<<< orphan*/ ) ; 
 struct radix_node* stub3 (struct sockaddr*,struct sockaddr*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct rtentry *
rt_unlinkrte(struct rib_head *rnh, struct rt_addrinfo *info, int *perror)
{
	struct sockaddr *dst, *netmask;
	struct rtentry *rt;
	struct radix_node *rn;

	dst = info->rti_info[RTAX_DST];
	netmask = info->rti_info[RTAX_NETMASK];

	rt = (struct rtentry *)rnh->rnh_lookup(dst, netmask, &rnh->head);
	if (rt == NULL) {
		*perror = ESRCH;
		return (NULL);
	}

	if ((info->rti_flags & RTF_PINNED) == 0) {
		/* Check if target route can be deleted */
		if (rt->rt_flags & RTF_PINNED) {
			*perror = EADDRINUSE;
			return (NULL);
		}
	}

	if (info->rti_filter != NULL) {
		if (info->rti_filter(rt, info->rti_filterdata) == 0) {
			/* Not matched */
			*perror = ENOENT;
			return (NULL);
		}

		/*
		 * Filter function requested rte deletion.
		 * Ease the caller work by filling in remaining info
		 * from that particular entry.
		 */
		info->rti_info[RTAX_GATEWAY] = rt->rt_gateway;
	}

	/*
	 * Remove the item from the tree and return it.
	 * Complain if it is not there and do no more processing.
	 */
	*perror = ESRCH;
#ifdef RADIX_MPATH
	if (rt_mpath_capable(rnh))
		rn = rt_mpath_unlink(rnh, info, rt, perror);
	else
#endif
	rn = rnh->rnh_deladdr(dst, netmask, &rnh->head);
	if (rn == NULL)
		return (NULL);

	if (rn->rn_flags & (RNF_ACTIVE | RNF_ROOT))
		panic ("rtrequest delete");

	rt = RNTORT(rn);
	RT_LOCK(rt);
	RT_ADDREF(rt);
	rt->rt_flags &= ~RTF_UP;

	*perror = 0;

	return (rt);
}