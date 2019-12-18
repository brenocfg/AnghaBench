#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  location_and_kind; } ;
typedef  TYPE_1__ working_node_version_t ;
typedef  scalar_t__ svn_wc_operation_t ;
struct TYPE_13__ {char const* path_in_repos; void* node_kind; } ;
typedef  TYPE_2__ svn_wc_conflict_version_t ;
typedef  int /*<<< orphan*/  svn_wc__db_t ;
typedef  int /*<<< orphan*/  svn_skel_t ;
typedef  void* svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 char const* svn_relpath_join (char const*,char const*,int /*<<< orphan*/ *) ; 
 char* svn_relpath_skip_ancestor (char const*,char const*) ; 
 int /*<<< orphan*/  svn_wc__conflict_create_markers (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__conflict_skel_set_op_merge (int /*<<< orphan*/ *,TYPE_2__*,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__conflict_skel_set_op_switch (int /*<<< orphan*/ *,TYPE_2__*,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__conflict_skel_set_op_update (int /*<<< orphan*/ *,TYPE_2__*,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_wc_conflict_version_dup (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_wc_operation_merge ; 
 scalar_t__ svn_wc_operation_update ; 

__attribute__((used)) static svn_error_t *
create_conflict_markers(svn_skel_t **work_items,
                        const char *local_abspath,
                        svn_wc__db_t *db,
                        const char *repos_relpath,
                        svn_skel_t *conflict_skel,
                        svn_wc_operation_t operation,
                        const working_node_version_t *old_version,
                        const working_node_version_t *new_version,
                        svn_node_kind_t kind,
                        svn_boolean_t set_operation,
                        apr_pool_t *result_pool,
                        apr_pool_t *scratch_pool)
{
  svn_wc_conflict_version_t *original_version;
  svn_wc_conflict_version_t *conflicted_version;
  const char *part;

  original_version = svn_wc_conflict_version_dup(
                       old_version->location_and_kind, scratch_pool);
  original_version->node_kind = kind;
  conflicted_version = svn_wc_conflict_version_dup(
                         new_version->location_and_kind, scratch_pool);
  conflicted_version->node_kind = kind;

  part = svn_relpath_skip_ancestor(original_version->path_in_repos,
                                   repos_relpath);
  if (part == NULL)
    part = svn_relpath_skip_ancestor(conflicted_version->path_in_repos,
                                     repos_relpath);
  SVN_ERR_ASSERT(part != NULL);

  conflicted_version->path_in_repos
    = svn_relpath_join(conflicted_version->path_in_repos, part, scratch_pool);
  original_version->path_in_repos = repos_relpath;

  if (set_operation)
    {
      if (operation == svn_wc_operation_update)
        {
          SVN_ERR(svn_wc__conflict_skel_set_op_update(
                    conflict_skel, original_version,
                    conflicted_version,
                    scratch_pool, scratch_pool));
        }
      else if (operation == svn_wc_operation_merge)
        {
          SVN_ERR(svn_wc__conflict_skel_set_op_merge(
                    conflict_skel, original_version,
                    conflicted_version,
                    scratch_pool, scratch_pool));
        }
      else
        {
          SVN_ERR(svn_wc__conflict_skel_set_op_switch(
                    conflict_skel, original_version,
                    conflicted_version,
                    scratch_pool, scratch_pool));
        }
    }

  /* According to this func's doc string, it is "Currently only used for
   * property conflicts as text conflict markers are just in-wc files." */
  SVN_ERR(svn_wc__conflict_create_markers(work_items, db,
                                          local_abspath,
                                          conflict_skel,
                                          result_pool,
                                          scratch_pool));

  return SVN_NO_ERROR;
}