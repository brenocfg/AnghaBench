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
struct mm_struct {int dummy; } ;

/* Variables and functions */
 scalar_t__ NO_CONTEXT ; 
 scalar_t__ cpu_context (int /*<<< orphan*/ ,struct mm_struct*) ; 
 int /*<<< orphan*/  flush_dcache_all () ; 
 int /*<<< orphan*/  smp_processor_id () ; 

__attribute__((used)) static void sh4_flush_cache_mm(void *arg)
{
	struct mm_struct *mm = arg;

	if (cpu_context(smp_processor_id(), mm) == NO_CONTEXT)
		return;

	flush_dcache_all();
}