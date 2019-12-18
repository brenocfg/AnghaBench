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
typedef  TYPE_1__* vm_page_t ;
typedef  scalar_t__ daddr_t ;
struct TYPE_3__ {int /*<<< orphan*/  pindex; int /*<<< orphan*/  object; } ;

/* Variables and functions */
 scalar_t__ SWAPBLK_NONE ; 
 int /*<<< orphan*/  SWM_POP ; 
 int /*<<< orphan*/  swp_pager_freeswapspace (scalar_t__,int) ; 
 scalar_t__ swp_pager_meta_ctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
swap_pager_unswapped(vm_page_t m)
{
	daddr_t srcaddr;

	srcaddr = swp_pager_meta_ctl(m->object, m->pindex, SWM_POP);
	if (srcaddr != SWAPBLK_NONE)
		swp_pager_freeswapspace(srcaddr, 1);
}