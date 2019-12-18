#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_mutex__t ;
typedef  TYPE_1__* (* svn_fs_upgrade_notify_t ) (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;
typedef  int /*<<< orphan*/  svn_fs_t ;
struct TYPE_14__ {int /*<<< orphan*/  apr_err; } ;
typedef  TYPE_1__ svn_error_t ;
typedef  int /*<<< orphan*/  svn_cancel_func_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 scalar_t__ APR_STATUS_IS_ENOENT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FORMAT_FILE ; 
 int /*<<< orphan*/  SVN_ERR (TYPE_1__*) ; 
 int /*<<< orphan*/  SVN_FS_BASE__FORMAT_NUMBER ; 
 int SVN_FS_BASE__MIN_FORWARD_DELTAS_FORMAT ; 
 int /*<<< orphan*/  SVN_FS_BASE__MISC_FORWARD_DELTA_UPGRADE ; 
 TYPE_1__* SVN_NO_ERROR ; 
 char* apr_psprintf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* base_open (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* check_format (int) ; 
 char* svn_dirent_join (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_1__*) ; 
 TYPE_1__* svn_fs_base__miscellaneous_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_fs_base__youngest_rev (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_upgrade_format_bumped ; 
 TYPE_1__* svn_io_read_version_file (int*,char const*,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_io_write_version_file (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
base_upgrade(svn_fs_t *fs,
             const char *path,
             svn_fs_upgrade_notify_t notify_func,
             void *notify_baton,
             svn_cancel_func_t cancel_func,
             void *cancel_baton,
             svn_mutex__t *common_pool_lock,
             apr_pool_t *pool,
             apr_pool_t *common_pool)
{
  const char *version_file_path;
  int old_format_number;
  svn_error_t *err;

  version_file_path = svn_dirent_join(path, FORMAT_FILE, pool);

  /* Read the old number so we've got it on hand later on. */
  err = svn_io_read_version_file(&old_format_number, version_file_path, pool);
  if (err && APR_STATUS_IS_ENOENT(err->apr_err))
    {
      /* Pre-1.2 filesystems do not have a 'format' file. */
      old_format_number = 0;
      svn_error_clear(err);
      err = SVN_NO_ERROR;
    }
  SVN_ERR(err);
  SVN_ERR(check_format(old_format_number));

  /* Bump the format file's stored version number. */
  SVN_ERR(svn_io_write_version_file(version_file_path,
                                    SVN_FS_BASE__FORMAT_NUMBER, pool));
  if (notify_func)
    SVN_ERR(notify_func(notify_baton, SVN_FS_BASE__FORMAT_NUMBER,
                        svn_fs_upgrade_format_bumped, pool));

  /* Check and see if we need to record the "bump" revision. */
  if (old_format_number < SVN_FS_BASE__MIN_FORWARD_DELTAS_FORMAT)
    {
      apr_pool_t *subpool = svn_pool_create(pool);
      svn_revnum_t youngest_rev;
      const char *value;

      /* Open the filesystem in a subpool (so we can control its
         closure) and do our fiddling.

         NOTE: By using base_open() here instead of open_databases(),
         we will end up re-reading the format file that we just wrote.
         But it's better to use the existing encapsulation of "opening
         the filesystem" rather than duplicating (or worse, partially
         duplicating) that logic here.  */
      SVN_ERR(base_open(fs, path, common_pool_lock, subpool, common_pool));

      /* Fetch the youngest rev, and record it */
      SVN_ERR(svn_fs_base__youngest_rev(&youngest_rev, fs, subpool));
      value = apr_psprintf(subpool, "%ld", youngest_rev);
      SVN_ERR(svn_fs_base__miscellaneous_set
              (fs, SVN_FS_BASE__MISC_FORWARD_DELTA_UPGRADE,
               value, subpool));
      svn_pool_destroy(subpool);
    }

  return SVN_NO_ERROR;
}