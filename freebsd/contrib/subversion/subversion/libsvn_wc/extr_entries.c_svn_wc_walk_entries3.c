#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_wc_entry_t ;
struct TYPE_22__ {TYPE_2__* (* handle_error ) (char const*,TYPE_2__*,void*,int /*<<< orphan*/ *) ;TYPE_2__* (* found_entry ) (char const*,int /*<<< orphan*/  const*,void*,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_1__ svn_wc_entry_callbacks2_t ;
typedef  int /*<<< orphan*/  svn_wc_adm_access_t ;
typedef  int /*<<< orphan*/  svn_wc__db_t ;
typedef  scalar_t__ svn_wc__db_status_t ;
typedef  scalar_t__ svn_node_kind_t ;
struct TYPE_23__ {scalar_t__ apr_err; } ;
typedef  TYPE_2__ svn_error_t ;
typedef  int /*<<< orphan*/  svn_depth_t ;
typedef  int /*<<< orphan*/  svn_cancel_func_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_NODE_UNKNOWN_KIND ; 
 int /*<<< orphan*/  SVN_ERR_UNVERSIONED_RESOURCE ; 
 scalar_t__ SVN_ERR_WC_PATH_NOT_FOUND ; 
 TYPE_2__* SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 TYPE_2__* stub1 (char const*,TYPE_2__*,void*,int /*<<< orphan*/ *) ; 
 TYPE_2__* stub2 (char const*,TYPE_2__*,void*,int /*<<< orphan*/ *) ; 
 TYPE_2__* stub3 (char const*,int /*<<< orphan*/  const*,void*,int /*<<< orphan*/ *) ; 
 TYPE_2__* stub4 (char const*,TYPE_2__*,void*,int /*<<< orphan*/ *) ; 
 TYPE_2__* stub5 (char const*,TYPE_2__*,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_get_absolute (char const**,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_local_style (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_2__*) ; 
 TYPE_2__* svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* svn_error_trace (TYPE_2__*) ; 
 scalar_t__ svn_node_dir ; 
 scalar_t__ svn_node_file ; 
 int /*<<< orphan*/ * svn_wc__adm_get_db (int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_wc__db_read_info (scalar_t__*,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_wc__db_status_excluded ; 
 scalar_t__ svn_wc__db_status_not_present ; 
 scalar_t__ svn_wc__db_status_server_excluded ; 
 int /*<<< orphan*/  svn_wc__get_entry (int /*<<< orphan*/  const**,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__* walker_helper (char const*,int /*<<< orphan*/ *,TYPE_1__ const*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc_walk_entries3(const char *path,
                     svn_wc_adm_access_t *adm_access,
                     const svn_wc_entry_callbacks2_t *walk_callbacks,
                     void *walk_baton,
                     svn_depth_t walk_depth,
                     svn_boolean_t show_hidden,
                     svn_cancel_func_t cancel_func,
                     void *cancel_baton,
                     apr_pool_t *pool)
{
  const char *local_abspath;
  svn_wc__db_t *db = svn_wc__adm_get_db(adm_access);
  svn_error_t *err;
  svn_node_kind_t kind;
  svn_wc__db_status_t status;

  SVN_ERR(svn_dirent_get_absolute(&local_abspath, path, pool));
  err = svn_wc__db_read_info(&status, &kind, NULL, NULL, NULL, NULL,
                             NULL, NULL, NULL, NULL, NULL, NULL,
                             NULL, NULL, NULL, NULL, NULL, NULL,
                             NULL, NULL, NULL, NULL, NULL, NULL,
                             NULL, NULL, NULL,
                             db, local_abspath,
                             pool, pool);
  if (err)
    {
      if (err->apr_err != SVN_ERR_WC_PATH_NOT_FOUND)
        return svn_error_trace(err);
      /* Remap into SVN_ERR_UNVERSIONED_RESOURCE.  */
      svn_error_clear(err);
      return walk_callbacks->handle_error(
        path, svn_error_createf(SVN_ERR_UNVERSIONED_RESOURCE, NULL,
                                _("'%s' is not under version control"),
                                svn_dirent_local_style(local_abspath, pool)),
        walk_baton, pool);
    }

  if (kind == svn_node_file
      || status == svn_wc__db_status_excluded
      || status == svn_wc__db_status_server_excluded)
    {
      const svn_wc_entry_t *entry;

      /* ### we should stop passing out entry structures.
         ###
         ### we should not call handle_error for an error the *callback*
         ###   gave us. let it deal with the problem before returning.  */

      if (!show_hidden
          && (status == svn_wc__db_status_not_present
              || status == svn_wc__db_status_excluded
              || status == svn_wc__db_status_server_excluded))
        {
          /* The fool asked to walk a "hidden" node. Report the node as
              unversioned.

              ### this is incorrect behavior. see depth_test 36. the walk
              ### API will be revamped to avoid entry structures. we should
              ### be able to solve the problem with the new API. (since we
              ### shouldn't return a hidden entry here)  */
          return walk_callbacks->handle_error(
                            path, svn_error_createf(
                              SVN_ERR_UNVERSIONED_RESOURCE, NULL,
                              _("'%s' is not under version control"),
                              svn_dirent_local_style(local_abspath, pool)),
                            walk_baton, pool);
        }

      SVN_ERR(svn_wc__get_entry(&entry, db, local_abspath, FALSE,
                                svn_node_file, pool, pool));

      err = walk_callbacks->found_entry(path, entry, walk_baton, pool);
      if (err)
        return walk_callbacks->handle_error(path, err, walk_baton, pool);

      return SVN_NO_ERROR;
    }

  if (kind == svn_node_dir)
    return walker_helper(path, adm_access, walk_callbacks, walk_baton,
                         walk_depth, show_hidden, cancel_func, cancel_baton,
                         pool);

  return walk_callbacks->handle_error(
       path, svn_error_createf(SVN_ERR_NODE_UNKNOWN_KIND, NULL,
                               _("'%s' has an unrecognized node kind"),
                               svn_dirent_local_style(local_abspath, pool)),
       walk_baton, pool);
}