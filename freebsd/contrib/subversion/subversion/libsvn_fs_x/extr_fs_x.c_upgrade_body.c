#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * fs; } ;
typedef  TYPE_1__ upgrade_baton_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int SVN_FS_X__FORMAT_NUMBER ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  read_format (int*,int*,char const*,int /*<<< orphan*/ *) ; 
 char* svn_fs_x__path_format (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
upgrade_body(void *baton,
             apr_pool_t *scratch_pool)
{
  upgrade_baton_t *upgrade_baton = baton;
  svn_fs_t *fs = upgrade_baton->fs;
  int format, max_files_per_dir;
  const char *format_path = svn_fs_x__path_format(fs, scratch_pool);

  /* Read the FS format number and max-files-per-dir setting. */
  SVN_ERR(read_format(&format, &max_files_per_dir, format_path,
                      scratch_pool));

  /* If we're already up-to-date, there's nothing else to be done here. */
  if (format == SVN_FS_X__FORMAT_NUMBER)
    return SVN_NO_ERROR;

  /* Done */
  return SVN_NO_ERROR;
}