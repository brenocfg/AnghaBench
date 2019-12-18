#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_wc_context_t ;
typedef  int /*<<< orphan*/  svn_wc_adm_access_t ;
struct TYPE_10__ {scalar_t__ apr_err; } ;
typedef  TYPE_1__ svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (TYPE_1__*) ; 
 scalar_t__ SVN_ERR_WC_NOT_WORKING_COPY ; 
 scalar_t__ SVN_ERR_WC_PATH_NOT_FOUND ; 
 TYPE_1__* SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 TYPE_1__* svn_dirent_get_absolute (char const**,char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_dirent_is_root (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_1__*) ; 
 TYPE_1__* svn_error_trace (int /*<<< orphan*/ ) ; 
 scalar_t__ svn_path_is_empty (char const*) ; 
 int /*<<< orphan*/  svn_wc__adm_get_db (int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_wc__context_create_with_db (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_context_destroy (int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_wc_is_wc_root2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc_is_wc_root(svn_boolean_t *wc_root,
                  const char *path,
                  svn_wc_adm_access_t *adm_access,
                  apr_pool_t *pool)
{
  svn_wc_context_t *wc_ctx;
  const char *local_abspath;
  svn_error_t *err;

  /* Subversion <= 1.6 said that '.' or a drive root is a WC root. */
  if (svn_path_is_empty(path) || svn_dirent_is_root(path, strlen(path)))
    {
      *wc_root = TRUE;
      return SVN_NO_ERROR;
    }

  SVN_ERR(svn_dirent_get_absolute(&local_abspath, path, pool));
  SVN_ERR(svn_wc__context_create_with_db(&wc_ctx, NULL /* config */,
                                         svn_wc__adm_get_db(adm_access),
                                         pool));

  err = svn_wc_is_wc_root2(wc_root, wc_ctx, local_abspath, pool);

  if (err
      && (err->apr_err == SVN_ERR_WC_NOT_WORKING_COPY
          || err->apr_err == SVN_ERR_WC_PATH_NOT_FOUND))
    {
      /* Subversion <= 1.6 said that an unversioned path is a WC root. */
      svn_error_clear(err);
      *wc_root = TRUE;
    }
  else
    SVN_ERR(err);

  return svn_error_trace(svn_wc_context_destroy(wc_ctx));
}