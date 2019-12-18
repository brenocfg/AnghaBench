#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_offset_t ;
struct tte {int tte_data; } ;
typedef  TYPE_2__* pmap_t ;
struct TYPE_6__ {int /*<<< orphan*/  wired_count; } ;
struct TYPE_7__ {TYPE_1__ pm_stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  PMAP_LOCK_ASSERT (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int TD_WIRED ; 
 int /*<<< orphan*/  atomic_clear_long (int*,int) ; 
 int /*<<< orphan*/  panic (char*,struct tte*) ; 

__attribute__((used)) static int
pmap_unwire_tte(pmap_t pm, pmap_t pm2, struct tte *tp, vm_offset_t va)
{

	PMAP_LOCK_ASSERT(pm, MA_OWNED);
	if ((tp->tte_data & TD_WIRED) == 0)
		panic("pmap_unwire_tte: tp %p is missing TD_WIRED", tp);
	atomic_clear_long(&tp->tte_data, TD_WIRED);
	pm->pm_stats.wired_count--;
	return (1);
}