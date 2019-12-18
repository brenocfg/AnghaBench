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
typedef  int /*<<< orphan*/  svn_repos_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_delta_editor_t ;
typedef  int /*<<< orphan*/  svn_commit_callback_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * svn_repos_get_commit_editor2 (int /*<<< orphan*/  const**,void**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,char const*,char const*,char const*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_repos_get_commit_editor(const svn_delta_editor_t **editor,
                            void **edit_baton,
                            svn_repos_t *repos,
                            const char *repos_url,
                            const char *base_path,
                            const char *user,
                            const char *log_msg,
                            svn_commit_callback_t callback,
                            void *callback_baton,
                            apr_pool_t *pool)
{
  return svn_repos_get_commit_editor2(editor, edit_baton, repos, NULL,
                                      repos_url, base_path, user,
                                      log_msg, callback,
                                      callback_baton, pool);
}