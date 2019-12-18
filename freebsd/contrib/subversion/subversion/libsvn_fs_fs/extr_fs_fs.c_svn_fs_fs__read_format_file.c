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
struct TYPE_5__ {TYPE_2__* fsap_data; } ;
typedef  TYPE_1__ svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct TYPE_6__ {int format; int max_files_per_dir; int /*<<< orphan*/  use_log_addressing; } ;
typedef  TYPE_2__ fs_fs_data_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  path_format (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_format (int*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_fs_fs__read_format_file(svn_fs_t *fs, apr_pool_t *scratch_pool)
{
  fs_fs_data_t *ffd = fs->fsap_data;
  int format, max_files_per_dir;
  svn_boolean_t use_log_addressing;

  /* Read info from format file. */
  SVN_ERR(read_format(&format, &max_files_per_dir, &use_log_addressing,
                      path_format(fs, scratch_pool), scratch_pool));

  /* Now that we've got *all* info, store / update values in FFD. */
  ffd->format = format;
  ffd->max_files_per_dir = max_files_per_dir;
  ffd->use_log_addressing = use_log_addressing;

  return SVN_NO_ERROR;
}