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
typedef  int /*<<< orphan*/  svn_mutex__t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_fs_pack_notify_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_cancel_func_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fs_open (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_fs_fs__pack (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
fs_pack(svn_fs_t *fs,
        const char *path,
        svn_fs_pack_notify_t notify_func,
        void *notify_baton,
        svn_cancel_func_t cancel_func,
        void *cancel_baton,
        svn_mutex__t *common_pool_lock,
        apr_pool_t *pool,
        apr_pool_t *common_pool)
{
  SVN_ERR(fs_open(fs, path, common_pool_lock, pool, common_pool));
  return svn_fs_fs__pack(fs, 0, notify_func, notify_baton,
                         cancel_func, cancel_baton, pool);
}