#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int rpcvers_t ;
typedef  scalar_t__ rpcprog_t ;
typedef  TYPE_2__* rpcblist_ptr ;
struct TYPE_4__ {scalar_t__ r_prog; unsigned int r_vers; int /*<<< orphan*/ * r_netid; } ;
struct TYPE_5__ {TYPE_1__ rpcb_map; struct TYPE_5__* rpcb_next; } ;

/* Variables and functions */
 TYPE_2__* list_rbl ; 
 scalar_t__ strcasecmp (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void
find_versions(rpcprog_t prog, char *netid, rpcvers_t *lowvp, rpcvers_t *highvp)
{
	register rpcblist_ptr rbl;
	unsigned int lowv = 0;
	unsigned int highv = 0;

	for (rbl = list_rbl; rbl != NULL; rbl = rbl->rpcb_next) {
		if ((rbl->rpcb_map.r_prog != prog) ||
		    ((rbl->rpcb_map.r_netid != NULL) &&
			(strcasecmp(rbl->rpcb_map.r_netid, netid) != 0)))
			continue;
		if (lowv == 0) {
			highv = rbl->rpcb_map.r_vers;
			lowv = highv;
		} else if (rbl->rpcb_map.r_vers < lowv) {
			lowv = rbl->rpcb_map.r_vers;
		} else if (rbl->rpcb_map.r_vers > highv) {
			highv = rbl->rpcb_map.r_vers;
		}
	}
	*lowvp = lowv;
	*highvp = highv;
	return;
}