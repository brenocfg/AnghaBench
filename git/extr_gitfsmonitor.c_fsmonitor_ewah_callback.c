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
struct index_state {struct cache_entry** cache; } ;
struct cache_entry {int /*<<< orphan*/  ce_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CE_FSMONITOR_VALID ; 

__attribute__((used)) static void fsmonitor_ewah_callback(size_t pos, void *is)
{
	struct index_state *istate = (struct index_state *)is;
	struct cache_entry *ce = istate->cache[pos];

	ce->ce_flags &= ~CE_FSMONITOR_VALID;
}