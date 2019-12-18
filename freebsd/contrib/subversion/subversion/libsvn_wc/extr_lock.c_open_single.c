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
typedef  int /*<<< orphan*/  svn_wc_adm_access_t ;
typedef  int /*<<< orphan*/  svn_wc__db_t ;
struct TYPE_10__ {int /*<<< orphan*/  apr_err; } ;
typedef  TYPE_1__ svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 scalar_t__ APR_STATUS_IS_ENOENT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (TYPE_1__*) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int) ; 
 int /*<<< orphan*/  SVN_ERR_WC_NOT_WORKING_COPY ; 
 TYPE_1__* SVN_NO_ERROR ; 
 int SVN_WC__VERSION ; 
 int /*<<< orphan*/  _ (char*) ; 
 TYPE_1__* adm_access_alloc (int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_dirent_get_absolute (char const**,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_local_style (char const*,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_error_createf (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* svn_wc__internal_check_wc (int*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
open_single(svn_wc_adm_access_t **adm_access,
            const char *path,
            svn_boolean_t write_lock,
            svn_wc__db_t *db,
            svn_boolean_t db_provided,
            apr_pool_t *result_pool,
            apr_pool_t *scratch_pool)
{
  const char *local_abspath;
  int wc_format = 0;
  svn_error_t *err;
  svn_wc_adm_access_t *lock;

  SVN_ERR(svn_dirent_get_absolute(&local_abspath, path, scratch_pool));
  err = svn_wc__internal_check_wc(&wc_format, db, local_abspath, FALSE,
                                  scratch_pool);
  if (wc_format == 0 || (err && APR_STATUS_IS_ENOENT(err->apr_err)))
    {
      return svn_error_createf(SVN_ERR_WC_NOT_WORKING_COPY, err,
                               _("'%s' is not a working copy"),
                               svn_dirent_local_style(path, scratch_pool));
    }
  SVN_ERR(err);

  /* The format version must match exactly. Note that wc_db will perform
     an auto-upgrade if allowed. If it does *not*, then it has decided a
     manual upgrade is required and it should have raised an error.  */
  SVN_ERR_ASSERT(wc_format == SVN_WC__VERSION);

  /* Need to create a new lock */
  SVN_ERR(adm_access_alloc(&lock, path, db, db_provided, write_lock,
                           result_pool, scratch_pool));

  /* ### recurse was here */
  *adm_access = lock;

  return SVN_NO_ERROR;
}