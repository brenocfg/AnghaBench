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
struct conflict_tree_incoming_add_details {int /*<<< orphan*/  deleted_rev; int /*<<< orphan*/  deleted_rev_author; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 char const* apr_psprintf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,scalar_t__,scalar_t__,int /*<<< orphan*/ ,...) ; 
 scalar_t__ rev_below (scalar_t__) ; 
 scalar_t__ svn_node_dir ; 
 scalar_t__ svn_node_file ; 
 scalar_t__ svn_node_symlink ; 

__attribute__((used)) static const char *
describe_incoming_reverse_deletion_upon_merge(
  struct conflict_tree_incoming_add_details *details,
  svn_node_kind_t new_node_kind,
  const char *old_repos_relpath,
  svn_revnum_t old_rev,
  svn_revnum_t new_rev,
  apr_pool_t *result_pool)
{
  if (new_node_kind == svn_node_dir)
    {
      if (new_rev + 1 == old_rev)
        return apr_psprintf(result_pool,
                            _("A new directory appeared during reverse-merge of"
                              "\n'^/%s:%ld'.\nIt was deleted by %s in r%ld."),
                            old_repos_relpath, old_rev,
                            details->deleted_rev_author,
                            details->deleted_rev);
      else
        return apr_psprintf(result_pool,
                            _("A new directory appeared during reverse-merge "
                              "of\n'^/%s:%ld-%ld'.\n"
                              "It was deleted by %s in r%ld."),
                            old_repos_relpath, new_rev, rev_below(old_rev),
                            details->deleted_rev_author,
                            details->deleted_rev);
    }
  else if (new_node_kind == svn_node_file ||
           new_node_kind == svn_node_symlink)
    {
      if (new_rev + 1 == old_rev)
        return apr_psprintf(result_pool,
                            _("A new file appeared during reverse-merge of\n"
                              "'^/%s:%ld'.\nIt was deleted by %s in r%ld."),
                            old_repos_relpath, old_rev,
                            details->deleted_rev_author,
                            details->deleted_rev);
      else
        return apr_psprintf(result_pool,
                            _("A new file appeared during reverse-merge of\n"
                              "'^/%s:%ld-%ld'.\nIt was deleted by %s in r%ld."),
                            old_repos_relpath, new_rev + 1, old_rev,
                            details->deleted_rev_author,
                            details->deleted_rev);
    }
  else
    {
      if (new_rev + 1 == old_rev)
        return apr_psprintf(result_pool,
                            _("A new item appeared during reverse-merge of\n"
                              "'^/%s:%ld'.\nIt was deleted by %s in r%ld."),
                            old_repos_relpath, old_rev,
                            details->deleted_rev_author,
                            details->deleted_rev);
      else
        return apr_psprintf(result_pool,
                            _("A new item appeared during reverse-merge of\n"
                              "'^/%s:%ld-%ld'.\nIt was deleted by %s in r%ld."),
                            old_repos_relpath, new_rev + 1, old_rev,
                            details->deleted_rev_author,
                            details->deleted_rev);
    }
}