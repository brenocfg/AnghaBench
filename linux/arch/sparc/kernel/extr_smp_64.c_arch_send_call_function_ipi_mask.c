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
typedef  int /*<<< orphan*/  u64 ;
struct cpumask {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  xcall_call_function ; 
 int /*<<< orphan*/  xcall_deliver (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cpumask const*) ; 

void arch_send_call_function_ipi_mask(const struct cpumask *mask)
{
	xcall_deliver((u64) &xcall_call_function, 0, 0, mask);
}