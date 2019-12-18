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
typedef  int u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct debug_store {int dummy; } ;
struct TYPE_2__ {struct debug_store* ds; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSR_IA32_DS_AREA ; 
 int /*<<< orphan*/  cpu_hw_events ; 
 TYPE_1__ per_cpu (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wrmsr_on_cpu (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void init_debug_store_on_cpu(int cpu)
{
	struct debug_store *ds = per_cpu(cpu_hw_events, cpu).ds;

	if (!ds)
		return;

	wrmsr_on_cpu(cpu, MSR_IA32_DS_AREA,
		     (u32)((u64)(unsigned long)ds),
		     (u32)((u64)(unsigned long)ds >> 32));
}