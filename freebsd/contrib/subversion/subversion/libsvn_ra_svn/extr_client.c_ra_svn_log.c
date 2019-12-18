#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_ra_session_t ;
typedef  int /*<<< orphan*/  svn_log_entry_receiver_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ensure_exact_server_parent (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perform_ra_svn_log (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * reparent_path_array (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_compose_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
ra_svn_log(svn_ra_session_t *session,
           const apr_array_header_t *paths,
           svn_revnum_t start, svn_revnum_t end,
           int limit,
           svn_boolean_t discover_changed_paths,
           svn_boolean_t strict_node_history,
           svn_boolean_t include_merged_revisions,
           const apr_array_header_t *revprops,
           svn_log_entry_receiver_t receiver,
           void *receiver_baton, apr_pool_t *pool)
{
  svn_error_t *outer_error = NULL;
  svn_error_t *err;

  /* If we don't specify paths, the session's URL is implied.

     Because the paths passed to callbacks are always relative the repos
     root, there is no need *always* sync the parent URLs despite invoking
     user-provided callbacks. */
  if (paths)
    paths = reparent_path_array(session, paths, pool);
  else
    SVN_ERR(ensure_exact_server_parent(session, pool));

  err = svn_error_trace(perform_ra_svn_log(&outer_error,
                                           session, paths,
                                           start, end,
                                           limit,
                                           discover_changed_paths,
                                           strict_node_history,
                                           include_merged_revisions,
                                           revprops,
                                           receiver, receiver_baton,
                                           pool));
  return svn_error_trace(
            svn_error_compose_create(outer_error,
                                     err));
}