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
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_MUTEX__WITH_LOCK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  fs_serialized_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  initialize_fs_struct (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs__check_fs (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_fs__create (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_fs__initialize_caches (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
fs_create(svn_fs_t *fs,
          const char *path,
          svn_mutex__t *common_pool_lock,
          apr_pool_t *scratch_pool,
          apr_pool_t *common_pool)
{
  SVN_ERR(svn_fs__check_fs(fs, FALSE));

  SVN_ERR(initialize_fs_struct(fs));

  SVN_ERR(svn_fs_fs__create(fs, path, scratch_pool));

  SVN_ERR(svn_fs_fs__initialize_caches(fs, scratch_pool));
  SVN_MUTEX__WITH_LOCK(common_pool_lock,
                       fs_serialized_init(fs, common_pool, scratch_pool));

  return SVN_NO_ERROR;
}