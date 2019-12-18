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
struct index_state {int dummy; } ;
struct cache_entry {int /*<<< orphan*/  name; int /*<<< orphan*/  ce_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CE_FSMONITOR_VALID ; 
 scalar_t__ core_fsmonitor ; 
 int /*<<< orphan*/  trace_fsmonitor ; 
 int /*<<< orphan*/  trace_printf_key (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  untracked_cache_invalidate_path (struct index_state*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void mark_fsmonitor_invalid(struct index_state *istate, struct cache_entry *ce)
{
	if (core_fsmonitor) {
		ce->ce_flags &= ~CE_FSMONITOR_VALID;
		untracked_cache_invalidate_path(istate, ce->name, 1);
		trace_printf_key(&trace_fsmonitor, "mark_fsmonitor_invalid '%s'", ce->name);
	}
}