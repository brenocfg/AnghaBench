#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int operation; int /*<<< orphan*/ * src_right_version; int /*<<< orphan*/ * src_left_version; int /*<<< orphan*/  action; int /*<<< orphan*/  reason; } ;
typedef  TYPE_1__ svn_wc_conflict_description2_t ;
typedef  int /*<<< orphan*/  svn_wc__db_t ;
typedef  int /*<<< orphan*/  svn_skel_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  apr_hash_make (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_dirname (char const*,int /*<<< orphan*/ *) ; 
 char* svn_dirent_join (char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_skel__parse (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__conflict_skel_add_prop_conflict (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__conflict_skel_add_text_conflict (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,char const*,char const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__conflict_skel_add_tree_conflict (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_wc__conflict_skel_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__conflict_skel_set_op_merge (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__conflict_skel_set_op_switch (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__conflict_skel_set_op_update (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_get_wcroot (char const**,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__deserialize_conflict (TYPE_1__ const**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
#define  svn_wc_operation_merge 130 
#define  svn_wc_operation_switch 129 
#define  svn_wc_operation_update 128 

svn_error_t *
svn_wc__upgrade_conflict_skel_from_raw(svn_skel_t **conflicts,
                                       svn_wc__db_t *db,
                                       const char *wri_abspath,
                                       const char *local_relpath,
                                       const char *conflict_old,
                                       const char *conflict_wrk,
                                       const char *conflict_new,
                                       const char *prej_file,
                                       const char *tree_conflict_data,
                                       apr_size_t tree_conflict_len,
                                       apr_pool_t *result_pool,
                                       apr_pool_t *scratch_pool)
{
  svn_skel_t *conflict_data = NULL;
  const char *wcroot_abspath;

  SVN_ERR(svn_wc__db_get_wcroot(&wcroot_abspath, db, wri_abspath,
                                scratch_pool, scratch_pool));

  if (conflict_old || conflict_new || conflict_wrk)
    {
      const char *old_abspath = NULL;
      const char *new_abspath = NULL;
      const char *wrk_abspath = NULL;

      conflict_data = svn_wc__conflict_skel_create(result_pool);

      if (conflict_old)
        old_abspath = svn_dirent_join(wcroot_abspath, conflict_old,
                                      scratch_pool);

      if (conflict_new)
        new_abspath = svn_dirent_join(wcroot_abspath, conflict_new,
                                      scratch_pool);

      if (conflict_wrk)
        wrk_abspath = svn_dirent_join(wcroot_abspath, conflict_wrk,
                                      scratch_pool);

      SVN_ERR(svn_wc__conflict_skel_add_text_conflict(conflict_data,
                                                      db, wri_abspath,
                                                      wrk_abspath,
                                                      old_abspath,
                                                      new_abspath,
                                                      scratch_pool,
                                                      scratch_pool));
    }

  if (prej_file)
    {
      const char *prej_abspath;

      if (!conflict_data)
        conflict_data = svn_wc__conflict_skel_create(result_pool);

      prej_abspath = svn_dirent_join(wcroot_abspath, prej_file, scratch_pool);

      SVN_ERR(svn_wc__conflict_skel_add_prop_conflict(conflict_data,
                                                      db, wri_abspath,
                                                      prej_abspath,
                                                      NULL, NULL, NULL,
                                                apr_hash_make(scratch_pool),
                                                      scratch_pool,
                                                      scratch_pool));
    }

  if (tree_conflict_data)
    {
      svn_skel_t *tc_skel;
      const svn_wc_conflict_description2_t *tc;
      const char *local_abspath;

      if (!conflict_data)
        conflict_data = svn_wc__conflict_skel_create(scratch_pool);

      tc_skel = svn_skel__parse(tree_conflict_data, tree_conflict_len,
                                scratch_pool);

      local_abspath = svn_dirent_join(wcroot_abspath, local_relpath,
                                      scratch_pool);

      SVN_ERR(svn_wc__deserialize_conflict(&tc, tc_skel,
                                           svn_dirent_dirname(local_abspath,
                                                              scratch_pool),
                                           scratch_pool, scratch_pool));

      SVN_ERR(svn_wc__conflict_skel_add_tree_conflict(conflict_data,
                                                      db, wri_abspath,
                                                      tc->reason,
                                                      tc->action,
                                                      NULL,
                                                      scratch_pool,
                                                      scratch_pool));

      switch (tc->operation)
        {
          case svn_wc_operation_update:
          default:
            SVN_ERR(svn_wc__conflict_skel_set_op_update(conflict_data,
                                                       tc->src_left_version,
                                                       tc->src_right_version,
                                                       scratch_pool,
                                                       scratch_pool));
            break;
          case svn_wc_operation_switch:
            SVN_ERR(svn_wc__conflict_skel_set_op_switch(conflict_data,
                                                        tc->src_left_version,
                                                        tc->src_right_version,
                                                        scratch_pool,
                                                        scratch_pool));
            break;
          case svn_wc_operation_merge:
            SVN_ERR(svn_wc__conflict_skel_set_op_merge(conflict_data,
                                                       tc->src_left_version,
                                                       tc->src_right_version,
                                                       scratch_pool,
                                                       scratch_pool));
            break;
        }
    }
  else if (conflict_data)
    {
      SVN_ERR(svn_wc__conflict_skel_set_op_update(conflict_data, NULL, NULL,
                                                  scratch_pool,
                                                  scratch_pool));
    }

  *conflicts = conflict_data;
  return SVN_NO_ERROR;
}