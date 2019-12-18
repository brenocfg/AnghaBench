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
typedef  int u_long ;
typedef  int /*<<< orphan*/  u_int ;
struct sockaddr {int /*<<< orphan*/  sa_family; } ;
struct rtentry {int dummy; } ;
struct rt_addrinfo {struct sockaddr** rti_info; } ;
struct rib_head {int /*<<< orphan*/  head; struct radix_node* (* rnh_matchaddr ) (struct sockaddr*,int /*<<< orphan*/ *) ;} ;
struct radix_node {int rn_flags; } ;
typedef  int /*<<< orphan*/  info ;
struct TYPE_2__ {int /*<<< orphan*/  rts_unreach; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  RIB_LOCK_ASSERT (struct rib_head*) ; 
 int /*<<< orphan*/  RIB_RLOCK (struct rib_head*) ; 
 int /*<<< orphan*/  RIB_RLOCK_TRACKER ; 
 int /*<<< orphan*/  RIB_RUNLOCK (struct rib_head*) ; 
 int RNF_ROOT ; 
 struct rtentry* RNTORT (struct radix_node*) ; 
 size_t RTAX_DST ; 
 int RTF_RNH_LOCKED ; 
 int RTM_MISS ; 
 int /*<<< orphan*/  RT_ADDREF (struct rtentry*) ; 
 int /*<<< orphan*/  RT_LOCK (struct rtentry*) ; 
 TYPE_1__ V_rtstat ; 
 int /*<<< orphan*/  bzero (struct rt_addrinfo*,int) ; 
 int /*<<< orphan*/  rt_missmsg_fib (int,struct rt_addrinfo*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt_numfibs ; 
 struct rib_head* rt_tables_get_rnh (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct radix_node* stub1 (struct sockaddr*,int /*<<< orphan*/ *) ; 

struct rtentry *
rtalloc1_fib(struct sockaddr *dst, int report, u_long ignflags,
		    u_int fibnum)
{
	RIB_RLOCK_TRACKER;
	struct rib_head *rh;
	struct radix_node *rn;
	struct rtentry *newrt;
	struct rt_addrinfo info;
	int err = 0, msgtype = RTM_MISS;

	KASSERT((fibnum < rt_numfibs), ("rtalloc1_fib: bad fibnum"));
	rh = rt_tables_get_rnh(fibnum, dst->sa_family);
	newrt = NULL;
	if (rh == NULL)
		goto miss;

	/*
	 * Look up the address in the table for that Address Family
	 */
	if ((ignflags & RTF_RNH_LOCKED) == 0)
		RIB_RLOCK(rh);
#ifdef INVARIANTS
	else
		RIB_LOCK_ASSERT(rh);
#endif
	rn = rh->rnh_matchaddr(dst, &rh->head);
	if (rn && ((rn->rn_flags & RNF_ROOT) == 0)) {
		newrt = RNTORT(rn);
		RT_LOCK(newrt);
		RT_ADDREF(newrt);
		if ((ignflags & RTF_RNH_LOCKED) == 0)
			RIB_RUNLOCK(rh);
		return (newrt);

	} else if ((ignflags & RTF_RNH_LOCKED) == 0)
		RIB_RUNLOCK(rh);
	/*
	 * Either we hit the root or could not find any match,
	 * which basically means: "cannot get there from here".
	 */
miss:
	V_rtstat.rts_unreach++;

	if (report) {
		/*
		 * If required, report the failure to the supervising
		 * Authorities.
		 * For a delete, this is not an error. (report == 0)
		 */
		bzero(&info, sizeof(info));
		info.rti_info[RTAX_DST] = dst;
		rt_missmsg_fib(msgtype, &info, 0, err, fibnum);
	}
	return (newrt);
}