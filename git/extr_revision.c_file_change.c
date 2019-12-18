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
struct object_id {int dummy; } ;
struct TYPE_2__ {int has_changes; } ;
struct diff_options {TYPE_1__ flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  REV_TREE_DIFFERENT ; 
 int /*<<< orphan*/  tree_difference ; 

__attribute__((used)) static void file_change(struct diff_options *options,
		 unsigned old_mode, unsigned new_mode,
		 const struct object_id *old_oid,
		 const struct object_id *new_oid,
		 int old_oid_valid, int new_oid_valid,
		 const char *fullpath,
		 unsigned old_dirty_submodule, unsigned new_dirty_submodule)
{
	tree_difference = REV_TREE_DIFFERENT;
	options->flags.has_changes = 1;
}