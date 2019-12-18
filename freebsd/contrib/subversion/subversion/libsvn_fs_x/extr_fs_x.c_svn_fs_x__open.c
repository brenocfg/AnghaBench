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
struct TYPE_9__ {scalar_t__ youngest_rev_cache; } ;
typedef  TYPE_1__ svn_fs_x__data_t ;
struct TYPE_10__ {int /*<<< orphan*/  pool; int /*<<< orphan*/  path; TYPE_1__* fsap_data; } ;
typedef  TYPE_2__ svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  apr_pstrdup (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  read_config (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_global_config (TYPE_2__*) ; 
 int /*<<< orphan*/  read_uuid (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__read_format_file (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__update_min_unpacked_rev (TYPE_2__*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_fs_x__open(svn_fs_t *fs,
               const char *path,
               apr_pool_t *scratch_pool)
{
  svn_fs_x__data_t *ffd = fs->fsap_data;
  fs->path = apr_pstrdup(fs->pool, path);

  /* Read the FS format file. */
  SVN_ERR(svn_fs_x__read_format_file(fs, scratch_pool));

  /* Read in and cache the repository uuid. */
  SVN_ERR(read_uuid(fs, scratch_pool));

  /* Read the min unpacked revision. */
  SVN_ERR(svn_fs_x__update_min_unpacked_rev(fs, scratch_pool));

  /* Read the configuration file. */
  SVN_ERR(read_config(ffd, fs->path, fs->pool, scratch_pool));

  /* Global configuration options. */
  SVN_ERR(read_global_config(fs));

  ffd->youngest_rev_cache = 0;

  return SVN_NO_ERROR;
}