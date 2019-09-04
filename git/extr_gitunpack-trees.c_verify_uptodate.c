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
struct unpack_trees_options {int /*<<< orphan*/  skip_sparse_checkout; } ;
struct cache_entry {int ce_flags; } ;

/* Variables and functions */
 int CE_NEW_SKIP_WORKTREE ; 
 int /*<<< orphan*/  ERROR_NOT_UPTODATE_FILE ; 
 int verify_uptodate_1 (struct cache_entry const*,struct unpack_trees_options*,int /*<<< orphan*/ ) ; 

int verify_uptodate(const struct cache_entry *ce,
		    struct unpack_trees_options *o)
{
	if (!o->skip_sparse_checkout && (ce->ce_flags & CE_NEW_SKIP_WORKTREE))
		return 0;
	return verify_uptodate_1(ce, o, ERROR_NOT_UPTODATE_FILE);
}