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
typedef  TYPE_2__* rpcb_entry_list_ptr ;
struct TYPE_4__ {scalar_t__ r_maddr; } ;
struct TYPE_5__ {TYPE_1__ rpcb_entry_map; struct TYPE_5__* rpcb_entry_next; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 

__attribute__((used)) static void
free_rpcb_entry_list(rpcb_entry_list_ptr *rlistp)
{
	register rpcb_entry_list_ptr rbl, tmp;

	for (rbl = *rlistp; rbl != NULL; ) {
		tmp = rbl;
		rbl = rbl->rpcb_entry_next;
		free((char *)tmp->rpcb_entry_map.r_maddr);
		free((char *)tmp);
	}
	*rlistp = NULL;
}