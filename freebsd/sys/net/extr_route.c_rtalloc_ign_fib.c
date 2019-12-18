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
typedef  int /*<<< orphan*/  u_long ;
typedef  int /*<<< orphan*/  u_int ;
struct rtentry {int rt_flags; int /*<<< orphan*/ * rt_ifp; } ;
struct route {struct rtentry* ro_rt; int /*<<< orphan*/  ro_dst; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTFREE (struct rtentry*) ; 
 int RTF_UP ; 
 int /*<<< orphan*/  RT_UNLOCK (struct rtentry*) ; 
 struct rtentry* rtalloc1_fib (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
rtalloc_ign_fib(struct route *ro, u_long ignore, u_int fibnum)
{
	struct rtentry *rt;

	if ((rt = ro->ro_rt) != NULL) {
		if (rt->rt_ifp != NULL && rt->rt_flags & RTF_UP)
			return;
		RTFREE(rt);
		ro->ro_rt = NULL;
	}
	ro->ro_rt = rtalloc1_fib(&ro->ro_dst, 1, ignore, fibnum);
	if (ro->ro_rt)
		RT_UNLOCK(ro->ro_rt);
}