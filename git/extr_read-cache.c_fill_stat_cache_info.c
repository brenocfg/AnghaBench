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
struct stat {int /*<<< orphan*/  st_mode; } ;
struct index_state {int dummy; } ;
struct cache_entry {int /*<<< orphan*/  ce_flags; int /*<<< orphan*/  ce_stat_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  CE_VALID ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 scalar_t__ assume_unchanged ; 
 int /*<<< orphan*/  ce_mark_uptodate (struct cache_entry*) ; 
 int /*<<< orphan*/  fill_stat_data (int /*<<< orphan*/ *,struct stat*) ; 
 int /*<<< orphan*/  mark_fsmonitor_valid (struct index_state*,struct cache_entry*) ; 

void fill_stat_cache_info(struct index_state *istate, struct cache_entry *ce, struct stat *st)
{
	fill_stat_data(&ce->ce_stat_data, st);

	if (assume_unchanged)
		ce->ce_flags |= CE_VALID;

	if (S_ISREG(st->st_mode)) {
		ce_mark_uptodate(ce);
		mark_fsmonitor_valid(istate, ce);
	}
}