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
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 char const* apr_psprintf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ svn_node_dir ; 
 scalar_t__ svn_node_file ; 
 scalar_t__ svn_node_symlink ; 

__attribute__((used)) static const char *
describe_incoming_edit_upon_switch(const char *new_repos_relpath,
                                   svn_revnum_t new_rev,
                                   svn_node_kind_t new_node_kind,
                                   apr_pool_t *result_pool)
{
  if (new_node_kind == svn_node_dir)
    return apr_psprintf(result_pool,
                        _("Changes destined for a directory arrived via "
                          "the following revisions during switch to\n"
                          "'^/%s@r%ld'"),
                        new_repos_relpath, new_rev);
  else if (new_node_kind == svn_node_file ||
           new_node_kind == svn_node_symlink)
    return apr_psprintf(result_pool,
                        _("Changes destined for a directory arrived via "
                          "the following revisions during switch to\n"
                          "'^/%s@r%ld'"),
                        new_repos_relpath, new_rev);
  else
    return apr_psprintf(result_pool,
                        _("Changes from the following revisions arrived "
                          "during switch to\n'^/%s@r%ld'"),
                        new_repos_relpath, new_rev);
}