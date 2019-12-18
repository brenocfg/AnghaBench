#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ svn_revnum_t ;
struct TYPE_4__ {int /*<<< orphan*/  path; } ;
typedef  TYPE_1__ svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  PATH_REVS_DIR ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  hotcopy_remove_files (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_join (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
hotcopy_remove_rev_files(svn_fs_t *dst_fs,
                         svn_revnum_t start_rev,
                         svn_revnum_t end_rev,
                         int max_files_per_dir,
                         apr_pool_t *scratch_pool)
{
  SVN_ERR_ASSERT(start_rev <= end_rev);
  SVN_ERR(hotcopy_remove_files(dst_fs,
                               svn_dirent_join(dst_fs->path,
                                               PATH_REVS_DIR,
                                               scratch_pool),
                               start_rev, end_rev,
                               max_files_per_dir, scratch_pool));

  return SVN_NO_ERROR;
}