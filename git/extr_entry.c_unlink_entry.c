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
struct submodule {int dummy; } ;
struct cache_entry {int /*<<< orphan*/  name; int /*<<< orphan*/  ce_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  SUBMODULE_MOVE_HEAD_FORCE ; 
 int /*<<< orphan*/  ce_namelen (struct cache_entry const*) ; 
 int /*<<< orphan*/  check_leading_path (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ remove_or_warn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_dir_for_removal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct submodule* submodule_from_ce (struct cache_entry const*) ; 
 int /*<<< orphan*/  submodule_move_head (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void unlink_entry(const struct cache_entry *ce)
{
	const struct submodule *sub = submodule_from_ce(ce);
	if (sub) {
		/* state.force is set at the caller. */
		submodule_move_head(ce->name, "HEAD", NULL,
				    SUBMODULE_MOVE_HEAD_FORCE);
	}
	if (!check_leading_path(ce->name, ce_namelen(ce)))
		return;
	if (remove_or_warn(ce->ce_mode, ce->name))
		return;
	schedule_dir_for_removal(ce->name, ce_namelen(ce));
}