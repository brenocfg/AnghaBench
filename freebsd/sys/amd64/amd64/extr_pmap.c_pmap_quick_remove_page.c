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
 int /*<<< orphan*/  invlpg (scalar_t__) ; 
 int /*<<< orphan*/  mtx_unlock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pte_store (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ qframe ; 
 int /*<<< orphan*/  qframe_mtx ; 
 int /*<<< orphan*/  vtopte (scalar_t__) ; 

void
pmap_quick_remove_page(vm_offset_t addr)
{

	if (addr != qframe)
		return;
	pte_store(vtopte(qframe), 0);
	invlpg(qframe);
	mtx_unlock_spin(&qframe_mtx);
}