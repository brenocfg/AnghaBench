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
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  scalar_t__ svn_node_kind_t ;
struct conflict_tree_incoming_delete_details {scalar_t__ replacing_node_kind; int /*<<< orphan*/  added_rev; int /*<<< orphan*/  rev_author; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 char const* apr_psprintf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ svn_node_dir ; 
 scalar_t__ svn_node_file ; 
 scalar_t__ svn_node_symlink ; 

__attribute__((used)) static const char *
describe_incoming_reverse_addition_upon_update(
  struct conflict_tree_incoming_delete_details *details,
  svn_node_kind_t victim_node_kind,
  svn_revnum_t old_rev,
  svn_revnum_t new_rev,
  apr_pool_t *result_pool)
{
  if (details->replacing_node_kind == svn_node_file ||
      details->replacing_node_kind == svn_node_symlink)
    {
      if (victim_node_kind == svn_node_dir)
        return apr_psprintf(result_pool,
                            _("Directory updated backwards from r%ld to r%ld "
                              "was a file before the replacement made by %s "
                              "in r%ld."), old_rev, new_rev,
                            details->rev_author, details->added_rev);
      else if (victim_node_kind == svn_node_file ||
               victim_node_kind == svn_node_symlink)
        return apr_psprintf(result_pool,
                            _("File updated backwards from r%ld to r%ld was a "
                              "file from another line of history before the "
                              "replacement made by %s in r%ld."),
                            old_rev, new_rev,
                            details->rev_author, details->added_rev);
      else
        return apr_psprintf(result_pool,
                            _("Item updated backwards from r%ld to r%ld was "
                              "replaced with a file by %s in r%ld."),
                            old_rev, new_rev,
                            details->rev_author, details->added_rev);
    }
  else if (details->replacing_node_kind == svn_node_dir)
    {
      if (victim_node_kind == svn_node_dir)
        return apr_psprintf(result_pool,
                            _("Directory updated backwards from r%ld to r%ld "
                              "was a directory from another line of history "
                              "before the replacement made by %s in "
                              "r%ld."), old_rev, new_rev,
                            details->rev_author, details->added_rev);
      else if (victim_node_kind == svn_node_file ||
               victim_node_kind == svn_node_symlink)
        return apr_psprintf(result_pool,
                            _("File updated backwards from r%ld to r%ld was a "
                              "directory before the replacement made by %s "
                              "in r%ld."), old_rev, new_rev,
                            details->rev_author, details->added_rev);
      else
        return apr_psprintf(result_pool,
                            _("Item updated backwards from r%ld to r%ld was "
                              "replaced with a directory by %s in r%ld."),
                            old_rev, new_rev,
                            details->rev_author, details->added_rev);
    }
  else
    {
      if (victim_node_kind == svn_node_dir)
        return apr_psprintf(result_pool,
                            _("Directory updated backwards from r%ld to r%ld "
                              "did not exist before it was added by %s in "
                              "r%ld."), old_rev, new_rev,
                            details->rev_author, details->added_rev);
      else if (victim_node_kind == svn_node_file ||
               victim_node_kind == svn_node_symlink)
        return apr_psprintf(result_pool,
                            _("File updated backwards from r%ld to r%ld did "
                              "not exist before it was added by %s in r%ld."),
                            old_rev, new_rev,
                            details->rev_author, details->added_rev);
      else
        return apr_psprintf(result_pool,
                            _("Item updated backwards from r%ld to r%ld did "
                              "not exist before it was added by %s in r%ld."),
                            old_rev, new_rev,
                            details->rev_author, details->added_rev);
    }
}