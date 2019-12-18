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
typedef  int /*<<< orphan*/  svn_fs_x__batch_fsync_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  svn_fs_x__batch_fsync_new_path (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_copy_perms (char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_file_rename2 (char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_fs_x__move_into_place(const char *old_filename,
                          const char *new_filename,
                          const char *perms_reference,
                          svn_fs_x__batch_fsync_t *batch,
                          apr_pool_t *scratch_pool)
{
  /* Copying permissions is a no-op on WIN32. */
  SVN_ERR(svn_io_copy_perms(perms_reference, old_filename, scratch_pool));

  /* We use specific 'fsyncing move' Win32 API calls on Windows while the
   * directory update fsync is POSIX-only.  Moreover, there tend to be only
   * a few moved files (1 or 2) per batch.
   *
   * Therefore, we use the platform-optimized "immediate" fsyncs on all
   * non-POSIX platforms and the "scheduled" fsyncs on POSIX only.
   */
#if defined(SVN_ON_POSIX)
  /* Move the file into place. */
  SVN_ERR(svn_io_file_rename2(old_filename, new_filename, FALSE,
                              scratch_pool));

  /* Schedule for synchronization. */
  SVN_ERR(svn_fs_x__batch_fsync_new_path(batch, new_filename, scratch_pool));
#else
  SVN_ERR(svn_io_file_rename2(old_filename, new_filename, TRUE,
                              scratch_pool));
#endif

  return SVN_NO_ERROR;
}