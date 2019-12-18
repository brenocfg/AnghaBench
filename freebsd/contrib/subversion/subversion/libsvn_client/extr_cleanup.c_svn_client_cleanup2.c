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
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_client_ctx_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  do_cleanup (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_is_absolute (char const*) ; 

svn_error_t *
svn_client_cleanup2(const char *dir_abspath,
                    svn_boolean_t break_locks,
                    svn_boolean_t fix_recorded_timestamps,
                    svn_boolean_t clear_dav_cache,
                    svn_boolean_t vacuum_pristines,
                    svn_boolean_t include_externals,
                    svn_client_ctx_t *ctx,
                    apr_pool_t *scratch_pool)
{
  SVN_ERR_ASSERT(svn_dirent_is_absolute(dir_abspath));

  SVN_ERR(do_cleanup(dir_abspath,
                     break_locks,
                     fix_recorded_timestamps,
                     clear_dav_cache,
                     vacuum_pristines,
                     FALSE /* remove_unversioned_items */,
                     FALSE /* remove_ignored_items */,
                     include_externals,
                     ctx, scratch_pool));

  return SVN_NO_ERROR;
}