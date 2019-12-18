#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_revnum_t ;
struct TYPE_5__ {int /*<<< orphan*/  path; TYPE_2__* fsap_data; } ;
typedef  TYPE_1__ svn_fs_t ;
struct TYPE_6__ {scalar_t__ max_files_per_dir; } ;
typedef  TYPE_2__ fs_fs_data_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  PATH_REVPROPS_DIR ; 
 int /*<<< orphan*/  SVN_VA_NULL ; 
 int /*<<< orphan*/  apr_psprintf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 char const* svn_dirent_join (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char const* svn_dirent_join_many (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_fs__path_revprops_shard (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

const char *
svn_fs_fs__path_revprops(svn_fs_t *fs,
                         svn_revnum_t rev,
                         apr_pool_t *pool)
{
  fs_fs_data_t *ffd = fs->fsap_data;

  if (ffd->max_files_per_dir)
    {
      return svn_dirent_join(svn_fs_fs__path_revprops_shard(fs, rev, pool),
                             apr_psprintf(pool, "%ld", rev),
                             pool);
    }

  return svn_dirent_join_many(pool, fs->path, PATH_REVPROPS_DIR,
                              apr_psprintf(pool, "%ld", rev), SVN_VA_NULL);
}