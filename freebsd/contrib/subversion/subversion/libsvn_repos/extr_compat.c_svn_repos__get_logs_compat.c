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
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_repos_t ;
typedef  int /*<<< orphan*/  svn_repos_authz_func_t ;
typedef  int /*<<< orphan*/  svn_log_entry_receiver_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
struct TYPE_4__ {void* inner_baton; int /*<<< orphan*/  inner; int /*<<< orphan*/ * changes; int /*<<< orphan*/ * changes_pool; } ;
typedef  TYPE_1__ log_entry_receiver_baton_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  log4_entry_receiver ; 
 int /*<<< orphan*/ * log4_path_change_receiver ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_repos_get_logs5 (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__,scalar_t__,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_repos__get_logs_compat(svn_repos_t *repos,
                           const apr_array_header_t *paths,
                           svn_revnum_t start,
                           svn_revnum_t end,
                           int limit,
                           svn_boolean_t discover_changed_paths,
                           svn_boolean_t strict_node_history,
                           svn_boolean_t include_merged_revisions,
                           const apr_array_header_t *revprops,
                           svn_repos_authz_func_t authz_read_func,
                           void *authz_read_baton,
                           svn_log_entry_receiver_t receiver,
                           void *receiver_baton,
                           apr_pool_t *pool)
{
  apr_pool_t *changes_pool = svn_pool_create(pool);

  log_entry_receiver_baton_t baton;
  baton.changes_pool = changes_pool;
  baton.changes = NULL;
  baton.inner = receiver;
  baton.inner_baton = receiver_baton;

  SVN_ERR(svn_repos_get_logs5(repos, paths, start, end, limit,
                              strict_node_history,
                              include_merged_revisions,
                              revprops,
                              authz_read_func, authz_read_baton,
                              discover_changed_paths
                                ? log4_path_change_receiver
                                : NULL,
                              &baton,
                              log4_entry_receiver, &baton,
                              pool));

  svn_pool_destroy(changes_pool);
  return SVN_NO_ERROR;
}