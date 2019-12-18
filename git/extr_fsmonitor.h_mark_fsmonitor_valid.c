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
struct index_state {int cache_changed; } ;
struct cache_entry {int ce_flags; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int CE_FSMONITOR_VALID ; 
 scalar_t__ core_fsmonitor ; 
 int /*<<< orphan*/  trace_fsmonitor ; 
 int /*<<< orphan*/  trace_printf_key (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void mark_fsmonitor_valid(struct index_state *istate, struct cache_entry *ce)
{
	if (core_fsmonitor && !(ce->ce_flags & CE_FSMONITOR_VALID)) {
		istate->cache_changed = 1;
		ce->ce_flags |= CE_FSMONITOR_VALID;
		trace_printf_key(&trace_fsmonitor, "mark_fsmonitor_clean '%s'", ce->name);
	}
}