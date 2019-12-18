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
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  svn_repos_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_cancel_func_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  enum svn_repos_load_uuid { ____Placeholder_svn_repos_load_uuid } svn_repos_load_uuid ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/ * repos_notify_handler ; 
 int /*<<< orphan*/ * svn_repos_load_fs3 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_repos_load_fs2(svn_repos_t *repos,
                   svn_stream_t *dumpstream,
                   svn_stream_t *feedback_stream,
                   enum svn_repos_load_uuid uuid_action,
                   const char *parent_dir,
                   svn_boolean_t use_pre_commit_hook,
                   svn_boolean_t use_post_commit_hook,
                   svn_cancel_func_t cancel_func,
                   void *cancel_baton,
                   apr_pool_t *pool)
{
  return svn_repos_load_fs3(repos, dumpstream, uuid_action, parent_dir,
                            use_pre_commit_hook, use_post_commit_hook, FALSE,
                            feedback_stream ? repos_notify_handler : NULL,
                            feedback_stream, cancel_func, cancel_baton, pool);
}