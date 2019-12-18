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
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_fs_x__batch_fsync_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_fs_x__batch_fsync_run (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__move_into_place (int /*<<< orphan*/ ,char const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* svn_fs_x__path_current (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__path_next (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_next_file (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
bump_current(svn_fs_t *fs,
             svn_revnum_t new_rev,
             svn_fs_x__batch_fsync_t *batch,
             apr_pool_t *scratch_pool)
{
  const char *current_filename;

  /* Write the 'next' file. */
  SVN_ERR(write_next_file(fs, new_rev, batch, scratch_pool));

  /* Commit all changes to disk. */
  SVN_ERR(svn_fs_x__batch_fsync_run(batch, scratch_pool));

  /* Make the revision visible to all processes and threads. */
  current_filename = svn_fs_x__path_current(fs, scratch_pool);
  SVN_ERR(svn_fs_x__move_into_place(svn_fs_x__path_next(fs, scratch_pool),
                                    current_filename, current_filename,
                                    batch, scratch_pool));

  /* Make the new revision permanently visible. */
  SVN_ERR(svn_fs_x__batch_fsync_run(batch, scratch_pool));

  return SVN_NO_ERROR;
}