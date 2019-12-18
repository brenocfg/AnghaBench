#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_wc_notify_state_t ;
struct TYPE_4__ {int /*<<< orphan*/  abspath; } ;
typedef  TYPE_1__ svn_wc__db_wcroot_t ;
typedef  int /*<<< orphan*/  svn_wc__db_t ;
typedef  int /*<<< orphan*/  svn_skel_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 scalar_t__ apr_hash_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_hash_make (int /*<<< orphan*/ *) ; 
 char* svn_dirent_join (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_prop_diffs (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_op_set_props_internal (TYPE_1__*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__has_magic_property (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__merge_props (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
update_incoming_add_merge_props(svn_wc_notify_state_t *prop_state,
                                svn_skel_t **conflict_skel,
                                const char *local_relpath,
                                apr_hash_t *base_props,
                                apr_hash_t *working_props,
                                svn_wc__db_t *db,
                                svn_wc__db_wcroot_t *wcroot,
                                apr_pool_t *result_pool,
                                apr_pool_t *scratch_pool)
{
  apr_hash_t *new_actual_props;
  apr_array_header_t *propchanges;
  const char *local_abspath = svn_dirent_join(wcroot->abspath,
                                              local_relpath,
                                              scratch_pool);

  /*
   * Run a 3-way prop merge to update the props, using the empty props
   * as the merge base, the post-update props as the merge-left version, and
   * the current props of the added working file as the merge-right version.
   */
  SVN_ERR(svn_prop_diffs(&propchanges, working_props,
                         apr_hash_make(scratch_pool), scratch_pool));
  SVN_ERR(svn_wc__merge_props(conflict_skel, prop_state, &new_actual_props,
                              db, local_abspath,
                              apr_hash_make(scratch_pool),
                              base_props, working_props, propchanges,
                              result_pool, scratch_pool));

  /* Install the new actual props. */
  if (apr_hash_count(new_actual_props) > 0)
    SVN_ERR(svn_wc__db_op_set_props_internal(wcroot, local_relpath,
                                             new_actual_props,
                                             svn_wc__has_magic_property(
                                                      propchanges),
                                             scratch_pool));

  return SVN_NO_ERROR;
}