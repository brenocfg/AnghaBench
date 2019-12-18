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
typedef  int /*<<< orphan*/  pv_entry_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  pagedaemon_wakeup (int /*<<< orphan*/ ) ; 
 scalar_t__ pv_entry_count ; 
 scalar_t__ pv_entry_high_water ; 
 int /*<<< orphan*/  pvzone ; 
 int /*<<< orphan*/  uma_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static pv_entry_t
pmap_get_pv_entry(void)
{
	pv_entry_t ret_value;

	pv_entry_count++;
	if (pv_entry_count > pv_entry_high_water)
		pagedaemon_wakeup(0); /* XXX ARM NUMA */
	ret_value = uma_zalloc(pvzone, M_NOWAIT);
	return ret_value;
}