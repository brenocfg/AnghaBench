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
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_cancel_func_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  svn_dirent_get_absolute (char const**,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_wc__adm_get_db (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__context_create_with_db (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_adm_probe_try3 (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_context_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_delete4 (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc_delete3(const char *path,
               svn_wc_adm_access_t *adm_access,
               svn_cancel_func_t cancel_func,
               void *cancel_baton,
               svn_wc_notify_func2_t notify_func,
               void *notify_baton,
               svn_boolean_t keep_local,
               apr_pool_t *pool)
{
  svn_wc_context_t *wc_ctx;
  svn_wc__db_t *wc_db = svn_wc__adm_get_db(adm_access);
  svn_wc_adm_access_t *dir_access;
  const char *local_abspath;

  SVN_ERR(svn_wc__context_create_with_db(&wc_ctx, NULL, wc_db, pool));
  SVN_ERR(svn_dirent_get_absolute(&local_abspath, path, pool));

  /* Open access batons for everything below path, because we used to open
     these before. */
  SVN_ERR(svn_wc_adm_probe_try3(&dir_access, adm_access, path,
                                TRUE, -1, cancel_func, cancel_baton, pool));

  SVN_ERR(svn_wc_delete4(wc_ctx,
                         local_abspath,
                         keep_local,
                         TRUE,
                         cancel_func, cancel_baton,
                         notify_func, notify_baton,
                         pool));

  return svn_error_trace(svn_wc_context_destroy(wc_ctx));
}