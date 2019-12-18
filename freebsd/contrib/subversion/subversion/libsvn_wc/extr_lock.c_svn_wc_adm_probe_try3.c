#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_wc_adm_access_t ;
struct TYPE_6__ {scalar_t__ apr_err; } ;
typedef  TYPE_1__ svn_error_t ;
typedef  int /*<<< orphan*/  svn_cancel_func_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 scalar_t__ SVN_ERR_WC_NOT_LOCKED ; 
 scalar_t__ SVN_ERR_WC_NOT_WORKING_COPY ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_1__*) ; 
 int /*<<< orphan*/  svn_wc_adm_access_pool (int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_wc_adm_probe_open3 (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 TYPE_1__* svn_wc_adm_probe_retrieve (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc_adm_probe_try3(svn_wc_adm_access_t **adm_access,
                      svn_wc_adm_access_t *associated,
                      const char *path,
                      svn_boolean_t write_lock,
                      int levels_to_lock,
                      svn_cancel_func_t cancel_func,
                      void *cancel_baton,
                      apr_pool_t *pool)
{
  svn_error_t *err;

  err = svn_wc_adm_probe_retrieve(adm_access, associated, path, pool);

  /* SVN_ERR_WC_NOT_LOCKED would mean there was no access baton for
     path in associated, in which case we want to open an access
     baton and add it to associated. */
  if (err && (err->apr_err == SVN_ERR_WC_NOT_LOCKED))
    {
      svn_error_clear(err);
      err = svn_wc_adm_probe_open3(adm_access, associated,
                                   path, write_lock, levels_to_lock,
                                   cancel_func, cancel_baton,
                                   svn_wc_adm_access_pool(associated));

      /* If the path is not a versioned directory, we just return a
         null access baton with no error.  Note that of the errors we
         do report, the most important (and probably most likely) is
         SVN_ERR_WC_LOCKED.  That error would mean that someone else
         has this area locked, and we definitely want to bail in that
         case. */
      if (err && (err->apr_err == SVN_ERR_WC_NOT_WORKING_COPY))
        {
          svn_error_clear(err);
          *adm_access = NULL;
          err = NULL;
        }
    }

  return err;
}