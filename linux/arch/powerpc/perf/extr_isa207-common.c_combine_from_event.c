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

/* Variables and functions */
 int /*<<< orphan*/  CPU_FTR_ARCH_300 ; 
 unsigned long EVENT_COMBINE (int /*<<< orphan*/ ) ; 
 scalar_t__ cpu_has_feature (int /*<<< orphan*/ ) ; 
 unsigned long p9_EVENT_COMBINE (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned long combine_from_event(u64 event)
{
	if (cpu_has_feature(CPU_FTR_ARCH_300))
		return p9_EVENT_COMBINE(event);

	return EVENT_COMBINE(event);
}