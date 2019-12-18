#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  min_unpacked_rev; int /*<<< orphan*/  max_files_per_dir; } ;
typedef  TYPE_1__ svn_fs_x__data_t ;
struct TYPE_7__ {TYPE_1__* fsap_data; } ;
typedef  TYPE_2__ svn_fs_t ;
struct TYPE_8__ {int /*<<< orphan*/  min_unpacked_rev; int /*<<< orphan*/  shard_size; int /*<<< orphan*/  fs_type; } ;
typedef  TYPE_3__ svn_fs_fsx_info_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_FS_TYPE_FSX ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 TYPE_3__* apr_palloc (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static svn_error_t *
x_info(const void **fsx_info,
       svn_fs_t *fs,
       apr_pool_t *result_pool,
       apr_pool_t *scratch_pool)
{
  svn_fs_x__data_t *ffd = fs->fsap_data;
  svn_fs_fsx_info_t *info = apr_palloc(result_pool, sizeof(*info));
  info->fs_type = SVN_FS_TYPE_FSX;
  info->shard_size = ffd->max_files_per_dir;
  info->min_unpacked_rev = ffd->min_unpacked_rev;
  *fsx_info = info;
  return SVN_NO_ERROR;
}