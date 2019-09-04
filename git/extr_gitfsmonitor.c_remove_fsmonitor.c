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
struct index_state {scalar_t__ fsmonitor_last_update; int /*<<< orphan*/  cache_changed; } ;

/* Variables and functions */
 int /*<<< orphan*/  FSMONITOR_CHANGED ; 
 int /*<<< orphan*/  trace_fsmonitor ; 
 int /*<<< orphan*/  trace_printf_key (int /*<<< orphan*/ *,char*) ; 

void remove_fsmonitor(struct index_state *istate)
{
	if (istate->fsmonitor_last_update) {
		trace_printf_key(&trace_fsmonitor, "remove fsmonitor");
		istate->cache_changed |= FSMONITOR_CHANGED;
		istate->fsmonitor_last_update = 0;
	}
}