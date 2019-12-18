#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ rpcvers_t ;
typedef  scalar_t__ rpcprog_t ;
typedef  TYPE_2__* rpcblist_ptr ;
struct TYPE_5__ {scalar_t__ r_prog; scalar_t__ r_vers; int /*<<< orphan*/ * r_netid; } ;
struct TYPE_6__ {TYPE_1__ rpcb_map; struct TYPE_6__* rpcb_next; } ;

/* Variables and functions */
 TYPE_2__* list_rbl ; 
 scalar_t__ strcasecmp (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static rpcblist_ptr
find_service(rpcprog_t prog, rpcvers_t vers, char *netid)
{
	register rpcblist_ptr hit = NULL;
	register rpcblist_ptr rbl;

	for (rbl = list_rbl; rbl != NULL; rbl = rbl->rpcb_next) {
		if ((rbl->rpcb_map.r_prog != prog) ||
		    ((rbl->rpcb_map.r_netid != NULL) &&
			(strcasecmp(rbl->rpcb_map.r_netid, netid) != 0)))
			continue;
		hit = rbl;
		if (rbl->rpcb_map.r_vers == vers)
			break;
	}
	return (hit);
}