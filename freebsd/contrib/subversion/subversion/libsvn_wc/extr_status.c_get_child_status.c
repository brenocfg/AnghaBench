#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_wc_status_func4_t ;
struct TYPE_4__ {scalar_t__ kind; } ;
typedef  TYPE_1__ svn_io_dirent2_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  (* svn_cancel_func_t ) (void*) ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct walk_status_baton {int /*<<< orphan*/  db; int /*<<< orphan*/  check_working_copy; } ;
struct svn_wc__db_info_t {int dummy; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  get_repos_root_url_relpath (char const**,char const**,char const**,struct svn_wc__db_info_t const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  one_child_status (struct walk_status_baton const*,char const*,char const*,struct svn_wc__db_info_t const*,TYPE_1__ const*,char const*,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/  (*) (void*),void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_depth_empty ; 
 char* svn_dirent_dirname (char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_node_none ; 
 int /*<<< orphan*/  svn_wc__db_read_single_info (struct svn_wc__db_info_t const**,int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
get_child_status(const struct walk_status_baton *wb,
                 const char *local_abspath,
                 const struct svn_wc__db_info_t *info,
                 const svn_io_dirent2_t *dirent,
                 const apr_array_header_t *ignore_patterns,
                 svn_boolean_t get_all,
                 svn_wc_status_func4_t status_func,
                 void *status_baton,
                 svn_cancel_func_t cancel_func,
                 void *cancel_baton,
                 apr_pool_t *scratch_pool)
{
  const char *dir_repos_root_url;
  const char *dir_repos_relpath;
  const char *dir_repos_uuid;
  const struct svn_wc__db_info_t *dir_info;
  apr_array_header_t *collected_ignore_patterns = NULL;
  const char *parent_abspath = svn_dirent_dirname(local_abspath,
                                                  scratch_pool);

  if (cancel_func)
    SVN_ERR(cancel_func(cancel_baton));

  if (dirent->kind == svn_node_none)
    dirent = NULL;

  SVN_ERR(svn_wc__db_read_single_info(&dir_info,
                                      wb->db, parent_abspath,
                                      !wb->check_working_copy,
                                      scratch_pool, scratch_pool));

  SVN_ERR(get_repos_root_url_relpath(&dir_repos_relpath, &dir_repos_root_url,
                                     &dir_repos_uuid, dir_info,
                                     NULL, NULL, NULL,
                                     wb->db, parent_abspath,
                                     scratch_pool, scratch_pool));

  /* An unversioned node with a tree conflict will see an INFO != NULL here,
   * in which case the FALSE passed for UNVERSIONED_TREE_CONFLICTED has no
   * effect and INFO->CONFLICTED counts.
   * ### Maybe svn_wc__db_read_children_info() and read_info() should be more
   * ### alike? */
  SVN_ERR(one_child_status(wb,
                           local_abspath,
                           parent_abspath,
                           info,
                           dirent,
                           dir_repos_root_url,
                           dir_repos_relpath,
                           dir_repos_uuid,
                           FALSE, /* unversioned_tree_conflicted */
                           &collected_ignore_patterns,
                           ignore_patterns,
                           svn_depth_empty,
                           get_all,
                           TRUE, /* no_ignore. This is an explicit target. */
                           status_func,
                           status_baton,
                           cancel_func,
                           cancel_baton,
                           scratch_pool,
                           scratch_pool));
  return SVN_NO_ERROR;
}