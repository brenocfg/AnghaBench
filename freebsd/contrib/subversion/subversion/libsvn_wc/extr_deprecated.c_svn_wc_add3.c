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
typedef  int /*<<< orphan*/  svn_wc_notify_func2_t ;
typedef  int /*<<< orphan*/  svn_wc_context_t ;
typedef  int /*<<< orphan*/  svn_wc_adm_access_t ;
typedef  int /*<<< orphan*/  svn_wc__db_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  scalar_t__ svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_depth_t ;
typedef  int /*<<< orphan*/  svn_cancel_func_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  svn_dirent_get_absolute (char const**,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 scalar_t__ svn_node_dir ; 
 int /*<<< orphan*/ * svn_wc__adm_get_db (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_wc__adm_retrieve_internal2 (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__context_create_with_db (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_read_kind (scalar_t__*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_add4 (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_adm_access_pool (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_adm_open3 (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_wc_context_destroy (int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc_add3(const char *path,
            svn_wc_adm_access_t *parent_access,
            svn_depth_t depth,
            const char *copyfrom_url,
            svn_revnum_t copyfrom_rev,
            svn_cancel_func_t cancel_func,
            void *cancel_baton,
            svn_wc_notify_func2_t notify_func,
            void *notify_baton,
            apr_pool_t *pool)
{
  svn_wc_context_t *wc_ctx;
  svn_wc__db_t *wc_db = svn_wc__adm_get_db(parent_access);
  const char *local_abspath;

  SVN_ERR(svn_wc__context_create_with_db(&wc_ctx, NULL, wc_db, pool));
  SVN_ERR(svn_dirent_get_absolute(&local_abspath, path, pool));

  SVN_ERR(svn_wc_add4(wc_ctx, local_abspath,
                      depth, copyfrom_url,
                      copyfrom_rev,
                      cancel_func, cancel_baton,
                      notify_func, notify_baton, pool));

  /* Make sure the caller gets the new access baton in the set. */
  if (svn_wc__adm_retrieve_internal2(wc_db, local_abspath, pool) == NULL)
    {
      svn_node_kind_t kind;

      SVN_ERR(svn_wc__db_read_kind(&kind, wc_db, local_abspath,
                                   FALSE /* allow_missing */,
                                   TRUE /* show_deleted */,
                                   FALSE /* show_hidden */, pool));
      if (kind == svn_node_dir)
        {
          svn_wc_adm_access_t *adm_access;

          /* Open the access baton in adm_access' pool to give it the same
             lifetime */
          SVN_ERR(svn_wc_adm_open3(&adm_access, parent_access, path, TRUE,
                                   copyfrom_url ? -1 : 0,
                                   cancel_func, cancel_baton,
                                   svn_wc_adm_access_pool(parent_access)));
        }
    }

  return svn_error_trace(svn_wc_context_destroy(wc_ctx));
}