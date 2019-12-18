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
typedef  int /*<<< orphan*/  svn_wc_status_func4_t ;
struct TYPE_6__ {scalar_t__ kind; } ;
typedef  TYPE_1__ svn_io_dirent2_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_depth_t ;
typedef  int /*<<< orphan*/  svn_cancel_func_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct walk_status_baton {int /*<<< orphan*/  db; int /*<<< orphan*/  target_abspath; } ;
struct svn_wc__db_info_t {scalar_t__ status; scalar_t__ kind; scalar_t__ has_descendants; int /*<<< orphan*/  conflicted; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  collect_ignore_patterns (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_dir_status (struct walk_status_baton const*,char const*,int /*<<< orphan*/ ,char const*,char const*,char const*,struct svn_wc__db_info_t const*,TYPE_1__ const*,int /*<<< orphan*/  const*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  send_status_structure (struct walk_status_baton const*,char const*,char const*,char const*,char const*,struct svn_wc__db_info_t const*,TYPE_1__ const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  send_unversioned_item (struct walk_status_baton const*,char const*,TYPE_1__ const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ svn_depth_files ; 
 scalar_t__ svn_depth_infinity ; 
 int /*<<< orphan*/  svn_dirent_basename (char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_node_dir ; 
 scalar_t__ svn_node_unknown ; 
 scalar_t__ svn_wc__db_status_excluded ; 
 scalar_t__ svn_wc__db_status_normal ; 
 scalar_t__ svn_wc__db_status_not_present ; 
 scalar_t__ svn_wc__db_status_server_excluded ; 
 scalar_t__ svn_wc_is_adm_dir (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
one_child_status(const struct walk_status_baton *wb,
                 const char *local_abspath,
                 const char *parent_abspath,
                 const struct svn_wc__db_info_t *info,
                 const svn_io_dirent2_t *dirent,
                 const char *dir_repos_root_url,
                 const char *dir_repos_relpath,
                 const char *dir_repos_uuid,
                 svn_boolean_t unversioned_tree_conflicted,
                 apr_array_header_t **collected_ignore_patterns,
                 const apr_array_header_t *ignore_patterns,
                 svn_depth_t depth,
                 svn_boolean_t get_all,
                 svn_boolean_t no_ignore,
                 svn_wc_status_func4_t status_func,
                 void *status_baton,
                 svn_cancel_func_t cancel_func,
                 void *cancel_baton,
                 apr_pool_t *result_pool,
                 apr_pool_t *scratch_pool)
{
  svn_boolean_t conflicted = info ? info->conflicted
                                  : unversioned_tree_conflicted;

  if (info
      && info->status != svn_wc__db_status_not_present
      && info->status != svn_wc__db_status_excluded
      && info->status != svn_wc__db_status_server_excluded
      && !(info->kind == svn_node_unknown
           && info->status == svn_wc__db_status_normal))
    {
      if (depth == svn_depth_files
          && info->kind == svn_node_dir)
        {
          return SVN_NO_ERROR;
        }

      SVN_ERR(send_status_structure(wb, local_abspath,
                                    dir_repos_root_url,
                                    dir_repos_relpath,
                                    dir_repos_uuid,
                                    info, dirent, get_all,
                                    status_func, status_baton,
                                    scratch_pool));

      /* Descend in subdirectories. */
      if (depth == svn_depth_infinity
          && info->has_descendants /* is dir, or was dir and tc descendants */)
        {
          SVN_ERR(get_dir_status(wb, local_abspath, TRUE,
                                 dir_repos_root_url, dir_repos_relpath,
                                 dir_repos_uuid, info,
                                 dirent, ignore_patterns,
                                 svn_depth_infinity, get_all,
                                 no_ignore,
                                 status_func, status_baton,
                                 cancel_func, cancel_baton,
                                 scratch_pool));
        }

      return SVN_NO_ERROR;
    }

  /* If conflicted, fall right through to unversioned.
   * With depth_files, show all conflicts, even if their report is only
   * about directories. A tree conflict may actually report two different
   * kinds, so it's not so easy to define what depth=files means. We could go
   * look up the kinds in the conflict ... just show all. */
  if (! conflicted)
    {
      /* We have a node, but its not visible in the WC. It can be a marker
         node (not present, (server) excluded), *or* it can be the explictly
         passed target of the status walk operation that doesn't exist.

         We only report the node when the caller explicitly as
      */
      if (dirent == NULL && strcmp(wb->target_abspath, local_abspath) != 0)
        return SVN_NO_ERROR; /* Marker node */

      if (depth == svn_depth_files && dirent && dirent->kind == svn_node_dir)
        return SVN_NO_ERROR;

      if (svn_wc_is_adm_dir(svn_dirent_basename(local_abspath, NULL),
                            scratch_pool))
        return SVN_NO_ERROR;
    }

  /* The node exists on disk but there is no versioned information about it,
   * or it doesn't exist but is a tree conflicted path or should be
   * reported not-present. */

  /* Why pass ignore patterns on a tree conflicted node, even if it should
   * always show up in clients' status reports anyway? Because the calling
   * client decides whether to ignore, and thus this flag needs to be
   * determined.  For example, in 'svn status', plain unversioned nodes show
   * as '?  C', where ignored ones show as 'I  C'. */

  if (ignore_patterns && ! *collected_ignore_patterns)
    SVN_ERR(collect_ignore_patterns(collected_ignore_patterns,
                                    wb->db, parent_abspath, ignore_patterns,
                                    result_pool, scratch_pool));

  SVN_ERR(send_unversioned_item(wb,
                                local_abspath,
                                dirent,
                                conflicted,
                                *collected_ignore_patterns,
                                no_ignore,
                                status_func, status_baton,
                                scratch_pool));

  return SVN_NO_ERROR;
}