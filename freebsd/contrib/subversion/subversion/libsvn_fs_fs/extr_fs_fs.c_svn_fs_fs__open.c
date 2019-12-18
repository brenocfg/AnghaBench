#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  pool; int /*<<< orphan*/  path; TYPE_2__* fsap_data; } ;
typedef  TYPE_1__ svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_10__ {scalar_t__ format; scalar_t__ youngest_rev_cache; } ;
typedef  TYPE_2__ fs_fs_data_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ SVN_FS_FS__MIN_PACKED_FORMAT ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  apr_pstrdup (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  read_config (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_global_config (TYPE_1__*) ; 
 int /*<<< orphan*/  read_uuid (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_fs__read_format_file (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_fs__update_min_unpacked_rev (TYPE_1__*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_fs_fs__open(svn_fs_t *fs, const char *path, apr_pool_t *pool)
{
  fs_fs_data_t *ffd = fs->fsap_data;
  fs->path = apr_pstrdup(fs->pool, path);

  /* Read the FS format file. */
  SVN_ERR(svn_fs_fs__read_format_file(fs, pool));

  /* Read in and cache the repository uuid. */
  SVN_ERR(read_uuid(fs, pool));

  /* Read the min unpacked revision. */
  if (ffd->format >= SVN_FS_FS__MIN_PACKED_FORMAT)
    SVN_ERR(svn_fs_fs__update_min_unpacked_rev(fs, pool));

  /* Read the configuration file. */
  SVN_ERR(read_config(ffd, fs->path, fs->pool, pool));

  /* Global configuration options. */
  SVN_ERR(read_global_config(fs));

  ffd->youngest_rev_cache = 0;

  return SVN_NO_ERROR;
}