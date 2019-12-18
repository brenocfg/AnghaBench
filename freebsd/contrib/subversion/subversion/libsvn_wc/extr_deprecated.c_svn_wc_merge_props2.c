#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_wc_notify_state_t ;
typedef  int /*<<< orphan*/  svn_wc_context_t ;
typedef  scalar_t__ svn_wc_conflict_resolver_func_t ;
typedef  int /*<<< orphan*/  svn_wc_adm_access_t ;
struct TYPE_7__ {int apr_err; } ;
typedef  TYPE_1__ svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
struct conflict_func_1to2_baton {void* inner_baton; scalar_t__ inner_func; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_UNSUPPORTED_FEATURE ; 
 int SVN_ERR_UNVERSIONED_RESOURCE ; 
#define  SVN_ERR_WC_PATH_NOT_FOUND 129 
#define  SVN_ERR_WC_PATH_UNEXPECTED_STATUS 128 
 int /*<<< orphan*/  U_ (char*) ; 
 int /*<<< orphan*/ * conflict_func_1to2_wrapper ; 
 int /*<<< orphan*/  svn_dirent_get_absolute (char const**,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_compose_create (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_wc__adm_get_db (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__context_create_with_db (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_context_destroy (int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_wc_merge_props3 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,scalar_t__,int /*<<< orphan*/ *,struct conflict_func_1to2_baton*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc_merge_props2(svn_wc_notify_state_t *state,
                    const char *path,
                    svn_wc_adm_access_t *adm_access,
                    apr_hash_t *baseprops,
                    const apr_array_header_t *propchanges,
                    svn_boolean_t base_merge,
                    svn_boolean_t dry_run,
                    svn_wc_conflict_resolver_func_t conflict_func,
                    void *conflict_baton,
                    apr_pool_t *scratch_pool)
{
  const char *local_abspath;
  svn_error_t *err;
  svn_wc_context_t *wc_ctx;
  struct conflict_func_1to2_baton conflict_wrapper;

  if (base_merge && !dry_run)
    return svn_error_create(SVN_ERR_UNSUPPORTED_FEATURE, NULL,
                            U_("base_merge=TRUE is no longer supported; "
                               "see notes/api-errata/1.7/wc006.txt"));

  SVN_ERR(svn_dirent_get_absolute(&local_abspath, path, scratch_pool));

  conflict_wrapper.inner_func = conflict_func;
  conflict_wrapper.inner_baton = conflict_baton;

  SVN_ERR(svn_wc__context_create_with_db(&wc_ctx, NULL,
                                         svn_wc__adm_get_db(adm_access),
                                         scratch_pool));

  err = svn_wc_merge_props3(state,
                            wc_ctx,
                            local_abspath,
                            NULL /* left_version */,
                            NULL /* right_version */,
                            baseprops,
                            propchanges,
                            dry_run,
                            conflict_func ? conflict_func_1to2_wrapper
                                          : NULL,
                            &conflict_wrapper,
                            NULL, NULL,
                            scratch_pool);

  if (err)
    switch(err->apr_err)
      {
        case SVN_ERR_WC_PATH_NOT_FOUND:
        case SVN_ERR_WC_PATH_UNEXPECTED_STATUS:
          err->apr_err = SVN_ERR_UNVERSIONED_RESOURCE;
          break;
      }
  return svn_error_trace(
            svn_error_compose_create(err,
                                     svn_wc_context_destroy(wc_ctx)));
}