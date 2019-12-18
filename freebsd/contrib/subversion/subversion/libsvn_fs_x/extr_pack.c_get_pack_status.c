#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int svn_revnum_t ;
struct TYPE_6__ {int min_unpacked_rev; int max_files_per_dir; } ;
typedef  TYPE_1__ svn_fs_x__data_t ;
struct TYPE_7__ {TYPE_1__* fsap_data; } ;
typedef  TYPE_2__ svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int apr_int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  svn_fs_x__read_min_unpacked_rev (int*,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__youngest_rev (int*,TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
get_pack_status(svn_boolean_t *fully_packed,
                svn_fs_t *fs,
                apr_pool_t *scratch_pool)
{
  svn_fs_x__data_t *ffd = fs->fsap_data;
  apr_int64_t completed_shards;
  svn_revnum_t youngest;

  SVN_ERR(svn_fs_x__read_min_unpacked_rev(&ffd->min_unpacked_rev, fs,
                                          scratch_pool));

  SVN_ERR(svn_fs_x__youngest_rev(&youngest, fs, scratch_pool));
  completed_shards = (youngest + 1) / ffd->max_files_per_dir;

  /* See if we've already completed all possible shards thus far. */
  if (ffd->min_unpacked_rev == (completed_shards * ffd->max_files_per_dir))
    *fully_packed = TRUE;
  else
    *fully_packed = FALSE;

  return SVN_NO_ERROR;
}