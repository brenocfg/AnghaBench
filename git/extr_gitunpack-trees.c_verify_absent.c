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
typedef  enum unpack_trees_error_types { ____Placeholder_unpack_trees_error_types } unpack_trees_error_types ;

/* Variables and functions */
 int CE_NEW_SKIP_WORKTREE ; 
 int verify_absent_1 (struct cache_entry const*,int,struct unpack_trees_options*) ; 

__attribute__((used)) static int verify_absent(const struct cache_entry *ce,
			 enum unpack_trees_error_types error_type,
			 struct unpack_trees_options *o)
{
	if (!o->skip_sparse_checkout && (ce->ce_flags & CE_NEW_SKIP_WORKTREE))
		return 0;
	return verify_absent_1(ce, error_type, o);
}