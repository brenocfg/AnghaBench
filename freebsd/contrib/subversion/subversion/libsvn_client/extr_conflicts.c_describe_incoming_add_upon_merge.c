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
typedef  scalar_t__ svn_revnum_t ;
typedef  scalar_t__ svn_node_kind_t ;
struct conflict_tree_incoming_add_details {int /*<<< orphan*/  added_rev; int /*<<< orphan*/  added_rev_author; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 char const* apr_psprintf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,scalar_t__,scalar_t__,int /*<<< orphan*/ ,...) ; 
 scalar_t__ svn_node_dir ; 
 scalar_t__ svn_node_file ; 
 scalar_t__ svn_node_symlink ; 

__attribute__((used)) static const char *
describe_incoming_add_upon_merge(
  struct conflict_tree_incoming_add_details *details,
  svn_node_kind_t new_node_kind,
  svn_revnum_t old_rev,
  const char *new_repos_relpath,
  svn_revnum_t new_rev,
  apr_pool_t *result_pool)
{
  if (new_node_kind == svn_node_dir)
    {
      if (old_rev + 1 == new_rev)
        return apr_psprintf(result_pool,
                            _("A new directory appeared during merge of\n"
                              "'^/%s:%ld'.\nIt was added by %s in r%ld."),
                            new_repos_relpath, new_rev,
                            details->added_rev_author, details->added_rev);
      else
        return apr_psprintf(result_pool,
                            _("A new directory appeared during merge of\n"
                              "'^/%s:%ld-%ld'.\nIt was added by %s in r%ld."),
                            new_repos_relpath, old_rev + 1, new_rev,
                            details->added_rev_author, details->added_rev);
    }
  else if (new_node_kind == svn_node_file ||
           new_node_kind == svn_node_symlink)
    {
      if (old_rev + 1 == new_rev)
        return apr_psprintf(result_pool,
                            _("A new file appeared during merge of\n"
                              "'^/%s:%ld'.\nIt was added by %s in r%ld."),
                            new_repos_relpath, new_rev,
                            details->added_rev_author, details->added_rev);
      else
        return apr_psprintf(result_pool,
                            _("A new file appeared during merge of\n"
                              "'^/%s:%ld-%ld'.\nIt was added by %s in r%ld."),
                            new_repos_relpath, old_rev + 1, new_rev,
                            details->added_rev_author, details->added_rev);
    }
  else
    {
      if (old_rev + 1 == new_rev)
        return apr_psprintf(result_pool,
                            _("A new item appeared during merge of\n"
                              "'^/%s:%ld'.\nIt was added by %s in r%ld."),
                            new_repos_relpath, new_rev,
                            details->added_rev_author, details->added_rev);
      else
        return apr_psprintf(result_pool,
                            _("A new item appeared during merge of\n"
                              "'^/%s:%ld-%ld'.\nIt was added by %s in r%ld."),
                            new_repos_relpath, old_rev + 1, new_rev,
                            details->added_rev_author, details->added_rev);
    }
}