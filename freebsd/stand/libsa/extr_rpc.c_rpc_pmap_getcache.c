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
typedef  scalar_t__ u_int ;
struct TYPE_2__ {scalar_t__ s_addr; } ;
struct pmap_list {scalar_t__ prog; scalar_t__ vers; int port; TYPE_1__ addr; } ;
struct in_addr {scalar_t__ s_addr; } ;

/* Variables and functions */
 struct pmap_list* rpc_pmap_list ; 
 size_t rpc_pmap_num ; 

int
rpc_pmap_getcache(struct in_addr addr, u_int prog, u_int vers)
{
	struct pmap_list *pl;

	for (pl = rpc_pmap_list; pl < &rpc_pmap_list[rpc_pmap_num]; pl++) {
		if (pl->addr.s_addr == addr.s_addr &&
			pl->prog == prog && pl->vers == vers )
		{
			return (pl->port);
		}
	}
	return (-1);
}