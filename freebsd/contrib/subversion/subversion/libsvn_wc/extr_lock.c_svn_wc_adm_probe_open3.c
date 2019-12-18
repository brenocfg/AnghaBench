#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {int /*<<< orphan*/ * db; } ;
typedef  TYPE_1__ svn_wc_adm_access_t ;
typedef  int /*<<< orphan*/  svn_wc__db_t ;
typedef  scalar_t__ svn_node_kind_t ;
struct TYPE_20__ {scalar_t__ apr_err; } ;
typedef  TYPE_2__ svn_error_t ;
typedef  int /*<<< orphan*/  svn_cancel_func_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (TYPE_2__*) ; 
 scalar_t__ SVN_ERR_WC_NOT_WORKING_COPY ; 
 TYPE_2__* SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 TYPE_2__* probe (int /*<<< orphan*/ *,char const**,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_local_style (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_2__*) ; 
 int /*<<< orphan*/  svn_error_compose (TYPE_2__*,TYPE_2__*) ; 
 TYPE_2__* svn_error_createf (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* svn_io_check_path (char const*,scalar_t__*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_node_dir ; 
 TYPE_2__* svn_wc__db_close (int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_wc__db_open (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_wc_adm_open3 (TYPE_1__**,TYPE_1__*,char const*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc_adm_probe_open3(svn_wc_adm_access_t **adm_access,
                       svn_wc_adm_access_t *associated,
                       const char *path,
                       svn_boolean_t write_lock,
                       int levels_to_lock,
                       svn_cancel_func_t cancel_func,
                       void *cancel_baton,
                       apr_pool_t *pool)
{
  svn_error_t *err;
  const char *dir;

  if (associated == NULL)
    {
      svn_wc__db_t *db;

      /* Ugh. Too bad about having to open a DB.  */
      SVN_ERR(svn_wc__db_open(&db,
                              NULL /* ### config */, FALSE, TRUE, pool, pool));
      err = probe(db, &dir, path, pool);
      svn_error_clear(svn_wc__db_close(db));
      SVN_ERR(err);
    }
  else
    {
      SVN_ERR(probe(associated->db, &dir, path, pool));
    }

  /* If we moved up a directory, then the path is not a directory, or it
     is not under version control. In either case, the notion of
     levels_to_lock does not apply to the provided path.  Disable it so
     that we don't end up trying to lock more than we need.  */
  if (dir != path)
    levels_to_lock = 0;

  err = svn_wc_adm_open3(adm_access, associated, dir, write_lock,
                         levels_to_lock, cancel_func, cancel_baton, pool);
  if (err)
    {
      svn_error_t *err2;

      /* If we got an error on the parent dir, that means we failed to
         get an access baton for the child in the first place.  And if
         the reason we couldn't get the child access baton is that the
         child is not a versioned directory, then return an error
         about the child, not the parent. */
      svn_node_kind_t child_kind;
      if ((err2 = svn_io_check_path(path, &child_kind, pool)))
        {
          svn_error_compose(err, err2);
          return err;
        }

      if ((dir != path)
          && (child_kind == svn_node_dir)
          && (err->apr_err == SVN_ERR_WC_NOT_WORKING_COPY))
        {
          svn_error_clear(err);
          return svn_error_createf(SVN_ERR_WC_NOT_WORKING_COPY, NULL,
                                   _("'%s' is not a working copy"),
                                   svn_dirent_local_style(path, pool));
        }

      return err;
    }

  return SVN_NO_ERROR;
}