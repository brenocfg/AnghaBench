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
struct conflict_tree_incoming_add_details {int /*<<< orphan*/  deleted_rev; int /*<<< orphan*/  deleted_rev_author; int /*<<< orphan*/  added_rev; int /*<<< orphan*/  added_rev_author; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 scalar_t__ SVN_IS_VALID_REVNUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _ (char*) ; 
 char const* apr_psprintf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 scalar_t__ svn_node_dir ; 
 scalar_t__ svn_node_file ; 
 scalar_t__ svn_node_symlink ; 

__attribute__((used)) static const char *
describe_incoming_add_upon_update(
  struct conflict_tree_incoming_add_details *details,
  svn_node_kind_t new_node_kind,
  svn_revnum_t new_rev,
  apr_pool_t *result_pool)
{
  if (new_node_kind == svn_node_dir)
    {
      if (SVN_IS_VALID_REVNUM(details->added_rev) &&
          SVN_IS_VALID_REVNUM(details->deleted_rev))
        return apr_psprintf(result_pool,
                            _("A new directory appeared during update to r%ld; "
                              "it was added by %s in r%ld and later deleted "
                              "by %s in r%ld."), new_rev,
                            details->added_rev_author, details->added_rev,
                            details->deleted_rev_author, details->deleted_rev);
      else if (SVN_IS_VALID_REVNUM(details->added_rev))
        return apr_psprintf(result_pool,
                            _("A new directory appeared during update to r%ld; "
                              "it was added by %s in r%ld."), new_rev,
                            details->added_rev_author, details->added_rev);
      else
        return apr_psprintf(result_pool,
                            _("A new directory appeared during update to r%ld; "
                              "it was deleted by %s in r%ld."), new_rev,
                            details->deleted_rev_author, details->deleted_rev);
    }
  else if (new_node_kind == svn_node_file ||
           new_node_kind == svn_node_symlink)
    {
      if (SVN_IS_VALID_REVNUM(details->added_rev) &&
          SVN_IS_VALID_REVNUM(details->deleted_rev))
        return apr_psprintf(result_pool,
                            _("A new file appeared during update to r%ld; "
                              "it was added by %s in r%ld and later deleted "
                              "by %s in r%ld."), new_rev,
                            details->added_rev_author, details->added_rev,
                            details->deleted_rev_author, details->deleted_rev);
      else if (SVN_IS_VALID_REVNUM(details->added_rev))
        return apr_psprintf(result_pool,
                            _("A new file appeared during update to r%ld; "
                              "it was added by %s in r%ld."), new_rev,
                            details->added_rev_author, details->added_rev);
      else
        return apr_psprintf(result_pool,
                            _("A new file appeared during update to r%ld; "
                              "it was deleted by %s in r%ld."), new_rev,
                            details->deleted_rev_author, details->deleted_rev);
    }
  else
    {
      if (SVN_IS_VALID_REVNUM(details->added_rev) &&
          SVN_IS_VALID_REVNUM(details->deleted_rev))
        return apr_psprintf(result_pool,
                            _("A new item appeared during update to r%ld; "
                              "it was added by %s in r%ld and later deleted "
                              "by %s in r%ld."), new_rev,
                            details->added_rev_author, details->added_rev,
                            details->deleted_rev_author, details->deleted_rev);
      else if (SVN_IS_VALID_REVNUM(details->added_rev))
        return apr_psprintf(result_pool,
                            _("A new item appeared during update to r%ld; "
                              "it was added by %s in r%ld."), new_rev,
                            details->added_rev_author, details->added_rev);
      else
        return apr_psprintf(result_pool,
                            _("A new item appeared during update to r%ld; "
                              "it was deleted by %s in r%ld."), new_rev,
                            details->deleted_rev_author, details->deleted_rev);
    }
}