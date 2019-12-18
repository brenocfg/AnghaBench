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
typedef  int /*<<< orphan*/  svn_repos_authz_func_t ;
typedef  int /*<<< orphan*/  svn_fs_root_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_delta_editor_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_DEPTH_INFINITY_OR_FILES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_repos_dir_delta2 (int /*<<< orphan*/ *,char const*,char const*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/  const*,void*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_repos_dir_delta(svn_fs_root_t *src_root,
                    const char *src_parent_dir,
                    const char *src_entry,
                    svn_fs_root_t *tgt_root,
                    const char *tgt_fullpath,
                    const svn_delta_editor_t *editor,
                    void *edit_baton,
                    svn_repos_authz_func_t authz_read_func,
                    void *authz_read_baton,
                    svn_boolean_t text_deltas,
                    svn_boolean_t recurse,
                    svn_boolean_t entry_props,
                    svn_boolean_t ignore_ancestry,
                    apr_pool_t *pool)
{
  return svn_repos_dir_delta2(src_root,
                              src_parent_dir,
                              src_entry,
                              tgt_root,
                              tgt_fullpath,
                              editor,
                              edit_baton,
                              authz_read_func,
                              authz_read_baton,
                              text_deltas,
                              SVN_DEPTH_INFINITY_OR_FILES(recurse),
                              entry_props,
                              ignore_ancestry,
                              pool);
}