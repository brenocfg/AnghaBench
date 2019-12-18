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
struct TYPE_2__ {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  at91_suspend_sram_fn (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_cache_all () ; 
 int /*<<< orphan*/  outer_disable () ; 
 TYPE_1__ soc_pm ; 

__attribute__((used)) static int at91_suspend_finish(unsigned long val)
{
	flush_cache_all();
	outer_disable();

	at91_suspend_sram_fn(&soc_pm.data);

	return 0;
}