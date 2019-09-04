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
struct stat {int /*<<< orphan*/  st_mode; } ;
struct cache_entry {int /*<<< orphan*/  ce_mode; } ;
struct apply_state {TYPE_1__* repo; } ;
struct TYPE_2__ {int /*<<< orphan*/  index; } ;

/* Variables and functions */
 int CE_MATCH_IGNORE_SKIP_WORKTREE ; 
 int CE_MATCH_IGNORE_VALID ; 
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISGITLINK (int /*<<< orphan*/ ) ; 
 int ie_match_stat (int /*<<< orphan*/ ,struct cache_entry const*,struct stat*,int) ; 

__attribute__((used)) static int verify_index_match(struct apply_state *state,
			      const struct cache_entry *ce,
			      struct stat *st)
{
	if (S_ISGITLINK(ce->ce_mode)) {
		if (!S_ISDIR(st->st_mode))
			return -1;
		return 0;
	}
	return ie_match_stat(state->repo->index, ce, st,
			     CE_MATCH_IGNORE_VALID | CE_MATCH_IGNORE_SKIP_WORKTREE);
}