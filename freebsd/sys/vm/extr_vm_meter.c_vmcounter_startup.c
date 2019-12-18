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
typedef  int /*<<< orphan*/  counter_u64_t ;

/* Variables and functions */
 int /*<<< orphan*/  COUNTER_ARRAY_ALLOC (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  VM_METER_NCOUNTERS ; 
 int /*<<< orphan*/  vm_cnt ; 

__attribute__((used)) static void
vmcounter_startup(void)
{
	counter_u64_t *cnt = (counter_u64_t *)&vm_cnt;

	COUNTER_ARRAY_ALLOC(cnt, VM_METER_NCOUNTERS, M_WAITOK);
}