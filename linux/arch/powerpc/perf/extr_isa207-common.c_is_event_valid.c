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
typedef  int u64 ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_FTR_ARCH_300 ; 
 int EVENT_VALID_MASK ; 
 scalar_t__ cpu_has_feature (int /*<<< orphan*/ ) ; 
 int p9_EVENT_VALID_MASK ; 

__attribute__((used)) static bool is_event_valid(u64 event)
{
	u64 valid_mask = EVENT_VALID_MASK;

	if (cpu_has_feature(CPU_FTR_ARCH_300))
		valid_mask = p9_EVENT_VALID_MASK;

	return !(event & ~valid_mask);
}