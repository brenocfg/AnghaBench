#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int svn_revnum_t ;
struct TYPE_12__ {int max_files_per_dir; } ;
typedef  TYPE_1__ svn_fs_x__data_t ;
typedef  int /*<<< orphan*/  svn_fs_x__batch_fsync_t ;
struct TYPE_13__ {int /*<<< orphan*/  path; TYPE_1__* fsap_data; } ;
typedef  TYPE_2__ svn_fs_t ;
struct TYPE_14__ {int /*<<< orphan*/  apr_err; } ;
typedef  TYPE_3__ svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_OS_DEFAULT ; 
 int /*<<< orphan*/  APR_STATUS_IS_EEXIST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PATH_REVS_DIR ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 TYPE_3__* SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_dirent_join (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_3__*) ; 
 TYPE_3__* svn_error_trace (TYPE_3__*) ; 
 int /*<<< orphan*/  svn_fs_x__batch_fsync_new_path (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 char* svn_fs_x__path_shard (TYPE_2__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_copy_perms (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 TYPE_3__* svn_io_dir_make (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
auto_create_shard(svn_fs_t *fs,
                  svn_revnum_t revision,
                  svn_fs_x__batch_fsync_t *batch,
                  apr_pool_t *scratch_pool)
{
  svn_fs_x__data_t *ffd = fs->fsap_data;
  if (revision % ffd->max_files_per_dir == 0)
    {
      const char *new_dir = svn_fs_x__path_shard(fs, revision, scratch_pool);
      svn_error_t *err = svn_io_dir_make(new_dir, APR_OS_DEFAULT,
                                         scratch_pool);

      if (err && !APR_STATUS_IS_EEXIST(err->apr_err))
        return svn_error_trace(err);
      svn_error_clear(err);

      SVN_ERR(svn_io_copy_perms(svn_dirent_join(fs->path, PATH_REVS_DIR,
                                                scratch_pool),
                                new_dir, scratch_pool));
      SVN_ERR(svn_fs_x__batch_fsync_new_path(batch, new_dir, scratch_pool));
    }

  return SVN_NO_ERROR;
}