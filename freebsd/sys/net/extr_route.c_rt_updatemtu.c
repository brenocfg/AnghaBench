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
struct rib_head {int /*<<< orphan*/  head; int /*<<< orphan*/  (* rnh_walktree ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct if_mtuinfo*) ;} ;
struct ifnet {int dummy; } ;
struct if_mtuinfo {int /*<<< orphan*/  mtu; struct ifnet* ifp; } ;

/* Variables and functions */
 int AF_MAX ; 
 int /*<<< orphan*/  RIB_WLOCK (struct rib_head*) ; 
 int /*<<< orphan*/  RIB_WUNLOCK (struct rib_head*) ; 
 int /*<<< orphan*/  if_getmtu_family (struct ifnet*,int) ; 
 int /*<<< orphan*/  if_updatemtu_cb ; 
 int rt_numfibs ; 
 struct rib_head* rt_tables_get_rnh (int,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct if_mtuinfo*) ; 

void
rt_updatemtu(struct ifnet *ifp)
{
	struct if_mtuinfo ifmtu;
	struct rib_head *rnh;
	int i, j;

	ifmtu.ifp = ifp;

	/*
	 * Try to update rt_mtu for all routes using this interface
	 * Unfortunately the only way to do this is to traverse all
	 * routing tables in all fibs/domains.
	 */
	for (i = 1; i <= AF_MAX; i++) {
		ifmtu.mtu = if_getmtu_family(ifp, i);
		for (j = 0; j < rt_numfibs; j++) {
			rnh = rt_tables_get_rnh(j, i);
			if (rnh == NULL)
				continue;
			RIB_WLOCK(rnh);
			rnh->rnh_walktree(&rnh->head, if_updatemtu_cb, &ifmtu);
			RIB_WUNLOCK(rnh);
		}
	}
}