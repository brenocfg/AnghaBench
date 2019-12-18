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
typedef  scalar_t__ vm_offset_t ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pmap_kremove (scalar_t__) ; 
 scalar_t__ qmap_addr ; 
 int /*<<< orphan*/  qmap_mtx ; 

void
pmap_quick_remove_page(vm_offset_t addr)
{
	KASSERT(addr == qmap_addr,
	    ("pmap_quick_remove_page: invalid address"));
	mtx_assert(&qmap_mtx, MA_OWNED);
	pmap_kremove(addr);
	mtx_unlock(&qmap_mtx);
}