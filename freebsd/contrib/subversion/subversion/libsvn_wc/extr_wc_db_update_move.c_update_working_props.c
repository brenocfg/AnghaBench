#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_7__* wcroot; int /*<<< orphan*/  db; } ;
typedef  TYPE_1__ update_move_baton_t ;
typedef  int /*<<< orphan*/  svn_wc_notify_state_t ;
typedef  int /*<<< orphan*/  svn_skel_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct working_node_version_t {int /*<<< orphan*/ * props; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
struct TYPE_11__ {int /*<<< orphan*/  nelts; } ;
typedef  TYPE_2__ apr_array_header_t ;
struct TYPE_12__ {int /*<<< orphan*/  abspath; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_dirent_join (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_prop_diffs (TYPE_2__**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_op_set_props_internal (TYPE_7__*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_read_props_internal (int /*<<< orphan*/ **,TYPE_7__*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__has_magic_property (TYPE_2__*) ; 
 int /*<<< orphan*/  svn_wc__merge_props (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
update_working_props(svn_wc_notify_state_t *prop_state,
                     svn_skel_t **conflict_skel,
                     apr_array_header_t **propchanges,
                     apr_hash_t **actual_props,
                     update_move_baton_t *b,
                     const char *local_relpath,
                     const struct working_node_version_t *old_version,
                     const struct working_node_version_t *new_version,
                     apr_pool_t *result_pool,
                     apr_pool_t *scratch_pool)
{
  apr_hash_t *new_actual_props;
  apr_array_header_t *new_propchanges;

  /*
   * Run a 3-way prop merge to update the props, using the pre-update
   * props as the merge base, the post-update props as the
   * merge-left version, and the current props of the
   * moved-here working file as the merge-right version.
   */
  SVN_ERR(svn_wc__db_read_props_internal(actual_props,
                                         b->wcroot, local_relpath,
                                         result_pool, scratch_pool));
  SVN_ERR(svn_prop_diffs(propchanges, new_version->props, old_version->props,
                         result_pool));
  SVN_ERR(svn_wc__merge_props(conflict_skel, prop_state,
                              &new_actual_props,
                              b->db, svn_dirent_join(b->wcroot->abspath,
                                                     local_relpath,
                                                     scratch_pool),
                              old_version->props, old_version->props,
                              *actual_props, *propchanges,
                              result_pool, scratch_pool));

  /* Setting properties in ACTUAL_NODE with svn_wc__db_op_set_props_internal
     relies on NODES row being updated via a different route .

     This extra property diff makes sure we clear the actual row when
     the final result is unchanged properties. */
  SVN_ERR(svn_prop_diffs(&new_propchanges, new_actual_props, new_version->props,
                         scratch_pool));
  if (!new_propchanges->nelts)
    new_actual_props = NULL;

  /* Install the new actual props. */
  SVN_ERR(svn_wc__db_op_set_props_internal(b->wcroot, local_relpath,
                                           new_actual_props,
                                           svn_wc__has_magic_property(
                                                    *propchanges),
                                           scratch_pool));

  return SVN_NO_ERROR;
}