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
struct stat {int dummy; } ;
struct diff_flags {int /*<<< orphan*/  ignore_untracked_in_submodules; scalar_t__ dirty_submodules; int /*<<< orphan*/  ignore_dirty_submodules; scalar_t__ ignore_submodules; int /*<<< orphan*/  override_submodule_config; } ;
struct diff_options {struct diff_flags flags; TYPE_1__* repo; } ;
struct cache_entry {int /*<<< orphan*/  name; int /*<<< orphan*/  ce_mode; } ;
struct TYPE_2__ {int /*<<< orphan*/  index; } ;

/* Variables and functions */
 scalar_t__ S_ISGITLINK (int /*<<< orphan*/ ) ; 
 int ie_match_stat (int /*<<< orphan*/ ,struct cache_entry const*,struct stat*,unsigned int) ; 
 unsigned int is_submodule_modified (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_diffopt_flags_from_submodule_config (struct diff_options*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int match_stat_with_submodule(struct diff_options *diffopt,
				     const struct cache_entry *ce,
				     struct stat *st, unsigned ce_option,
				     unsigned *dirty_submodule)
{
	int changed = ie_match_stat(diffopt->repo->index, ce, st, ce_option);
	if (S_ISGITLINK(ce->ce_mode)) {
		struct diff_flags orig_flags = diffopt->flags;
		if (!diffopt->flags.override_submodule_config)
			set_diffopt_flags_from_submodule_config(diffopt, ce->name);
		if (diffopt->flags.ignore_submodules)
			changed = 0;
		else if (!diffopt->flags.ignore_dirty_submodules &&
			 (!changed || diffopt->flags.dirty_submodules))
			*dirty_submodule = is_submodule_modified(ce->name,
								 diffopt->flags.ignore_untracked_in_submodules);
		diffopt->flags = orig_flags;
	}
	return changed;
}