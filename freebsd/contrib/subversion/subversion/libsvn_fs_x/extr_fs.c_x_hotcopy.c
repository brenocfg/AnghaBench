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
typedef  int /*<<< orphan*/  svn_fs_hotcopy_notify_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  (* svn_cancel_func_t ) (void*) ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  initialize_fs_struct (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs__check_fs (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_fs_x__hotcopy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/  (*) (void*),void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  x_open (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
x_hotcopy(svn_fs_t *src_fs,
          svn_fs_t *dst_fs,
          const char *src_path,
          const char *dst_path,
          svn_boolean_t clean_logs,
          svn_boolean_t incremental,
          svn_fs_hotcopy_notify_t notify_func,
          void *notify_baton,
          svn_cancel_func_t cancel_func,
          void *cancel_baton,
          svn_mutex__t *common_pool_lock,
          apr_pool_t *scratch_pool,
          apr_pool_t *common_pool)
{
  /* Open the source repo as usual. */
  SVN_ERR(x_open(src_fs, src_path, common_pool_lock, scratch_pool,
                 common_pool));
  if (cancel_func)
    SVN_ERR(cancel_func(cancel_baton));

  SVN_ERR(svn_fs__check_fs(dst_fs, FALSE));
  SVN_ERR(initialize_fs_struct(dst_fs));

  /* In INCREMENTAL mode, svn_fs_x__hotcopy() will open DST_FS.
     Otherwise, it's not an FS yet --- possibly just an empty dir --- so
     can't be opened.
   */
  return svn_fs_x__hotcopy(src_fs, dst_fs, src_path, dst_path,
                            incremental, notify_func, notify_baton,
                            cancel_func, cancel_baton, common_pool_lock,
                            scratch_pool, common_pool);
}