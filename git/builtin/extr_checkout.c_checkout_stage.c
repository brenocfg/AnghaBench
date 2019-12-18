#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct checkout {int dummy; } ;
struct cache_entry {int /*<<< orphan*/  name; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 TYPE_1__** active_cache ; 
 int active_nr ; 
 int ce_stage (TYPE_1__*) ; 
 int checkout_entry (TYPE_1__*,struct checkout const*,int /*<<< orphan*/ *,int*) ; 
 int error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlink_entry (struct cache_entry const*) ; 

__attribute__((used)) static int checkout_stage(int stage, const struct cache_entry *ce, int pos,
			  const struct checkout *state, int *nr_checkouts,
			  int overlay_mode)
{
	while (pos < active_nr &&
	       !strcmp(active_cache[pos]->name, ce->name)) {
		if (ce_stage(active_cache[pos]) == stage)
			return checkout_entry(active_cache[pos], state,
					      NULL, nr_checkouts);
		pos++;
	}
	if (!overlay_mode) {
		unlink_entry(ce);
		return 0;
	}
	if (stage == 2)
		return error(_("path '%s' does not have our version"), ce->name);
	else
		return error(_("path '%s' does not have their version"), ce->name);
}