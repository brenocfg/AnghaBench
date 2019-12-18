#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int svn_revnum_t ;
struct TYPE_4__ {int /*<<< orphan*/  path; TYPE_2__* fsap_data; } ;
typedef  TYPE_1__ svn_fs_t ;
struct TYPE_5__ {int max_files_per_dir; } ;
typedef  TYPE_2__ fs_fs_data_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  PATH_REVPROPS_DIR ; 
 int /*<<< orphan*/  SVN_VA_NULL ; 
 int /*<<< orphan*/  apr_psprintf (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 char const* svn_dirent_join_many (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

const char *
svn_fs_fs__path_revprops_shard(svn_fs_t *fs,
                               svn_revnum_t rev,
                               apr_pool_t *pool)
{
  fs_fs_data_t *ffd = fs->fsap_data;

  assert(ffd->max_files_per_dir);
  return svn_dirent_join_many(pool, fs->path, PATH_REVPROPS_DIR,
                              apr_psprintf(pool, "%ld",
                                           rev / ffd->max_files_per_dir),
                              SVN_VA_NULL);
}