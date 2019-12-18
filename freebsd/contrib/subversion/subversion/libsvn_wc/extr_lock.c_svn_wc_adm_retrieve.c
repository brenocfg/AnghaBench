#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/  db; int /*<<< orphan*/  path; } ;
typedef  TYPE_1__ svn_wc_adm_access_t ;
typedef  scalar_t__ svn_node_kind_t ;
struct TYPE_17__ {int /*<<< orphan*/  message; } ;
typedef  TYPE_2__ svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_WC_NOT_LOCKED ; 
 int /*<<< orphan*/  SVN_ERR_WC_NOT_WORKING_COPY ; 
 int /*<<< orphan*/  SVN_ERR_WC_PATH_NOT_FOUND ; 
 TYPE_2__* SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  svn_dirent_get_absolute (char const**,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_local_style (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_2__*) ; 
 TYPE_2__* svn_error_create (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* svn_error_createf (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* svn_io_check_path (char const*,scalar_t__*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_node_dir ; 
 scalar_t__ svn_node_file ; 
 scalar_t__ svn_node_none ; 
 scalar_t__ svn_node_unknown ; 
 int /*<<< orphan*/  svn_wc__adm_get_db (TYPE_1__*) ; 
 TYPE_1__* svn_wc__adm_retrieve_internal2 (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_wc__db_read_kind (scalar_t__*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc_adm_retrieve(svn_wc_adm_access_t **adm_access,
                    svn_wc_adm_access_t *associated,
                    const char *path,
                    apr_pool_t *pool)
{
  const char *local_abspath;
  svn_node_kind_t kind = svn_node_unknown;
  svn_node_kind_t wckind;
  svn_error_t *err;

  SVN_ERR(svn_dirent_get_absolute(&local_abspath, path, pool));

  if (strcmp(associated->path, path) == 0)
    *adm_access = associated;
  else
    *adm_access = svn_wc__adm_retrieve_internal2(associated->db, local_abspath,
                                                 pool);

  /* We found what we're looking for, so bail. */
  if (*adm_access)
    return SVN_NO_ERROR;

  /* Most of the code expects access batons to exist, so returning an error
     generally makes the calling code simpler as it doesn't need to check
     for NULL batons. */
  /* We are going to send a SVN_ERR_WC_NOT_LOCKED, but let's provide
     a bit more information to our caller */

  err = svn_io_check_path(path, &wckind, pool);

  /* If we can't check the path, we can't make a good error message.  */
  if (err)
    {
      return svn_error_createf(SVN_ERR_WC_NOT_LOCKED, err,
                               _("Unable to check path existence for '%s'"),
                               svn_dirent_local_style(path, pool));
    }

  if (associated)
    {
      err = svn_wc__db_read_kind(&kind, svn_wc__adm_get_db(associated),
                                 local_abspath,
                                 TRUE /* allow_missing */,
                                 TRUE /* show_deleted */,
                                 FALSE /* show_hidden */, pool);

      if (err)
        {
          kind = svn_node_unknown;
          svn_error_clear(err);
        }
    }

  if (kind == svn_node_dir && wckind == svn_node_file)
    {
      err = svn_error_createf(
               SVN_ERR_WC_NOT_WORKING_COPY, NULL,
               _("Expected '%s' to be a directory but found a file"),
               svn_dirent_local_style(path, pool));

      return svn_error_create(SVN_ERR_WC_NOT_LOCKED, err, err->message);
    }

  if (kind != svn_node_dir && kind != svn_node_unknown)
    {
      err = svn_error_createf(
               SVN_ERR_WC_NOT_WORKING_COPY, NULL,
               _("Can't retrieve an access baton for non-directory '%s'"),
               svn_dirent_local_style(path, pool));

      return svn_error_create(SVN_ERR_WC_NOT_LOCKED, err, err->message);
    }

  if (kind == svn_node_unknown || wckind == svn_node_none)
    {
      err = svn_error_createf(SVN_ERR_WC_PATH_NOT_FOUND, NULL,
                              _("Directory '%s' is missing"),
                              svn_dirent_local_style(path, pool));

      return svn_error_create(SVN_ERR_WC_NOT_LOCKED, err, err->message);
    }

  /* If all else fails, return our useless generic error.  */
  return svn_error_createf(SVN_ERR_WC_NOT_LOCKED, NULL,
                           _("Working copy '%s' is not locked"),
                           svn_dirent_local_style(path, pool));
}