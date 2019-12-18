#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  scalar_t__ apr_status_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_3__ {scalar_t__ filetype; } ;
typedef  TYPE_1__ apr_finfo_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_FINFO_TYPE ; 
 scalar_t__ APR_FROM_OS_ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ APR_REG ; 
 scalar_t__ APR_STATUS_IS_EACCES (scalar_t__) ; 
 scalar_t__ APR_STATUS_IS_EEXIST (scalar_t__) ; 
 scalar_t__ APR_STATUS_IS_ENOENT (scalar_t__) ; 
 int /*<<< orphan*/  ERROR_ACCESS_DENIED ; 
 int /*<<< orphan*/  ERROR_SHARING_VIOLATION ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 scalar_t__ SVN__APR_STATUS_IS_ENOTDIR (scalar_t__) ; 
 int /*<<< orphan*/  WIN32_RETRY_LOOP (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ apr_file_remove (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_stat (TYPE_1__*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cstring_from_utf8 (char const**,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_local_style (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_wrap_apr (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_io_set_file_read_write (char const*,scalar_t__,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_io_remove_file2(const char *path,
                    svn_boolean_t ignore_enoent,
                    apr_pool_t *scratch_pool)
{
  apr_status_t apr_err;
  const char *path_apr;

  SVN_ERR(cstring_from_utf8(&path_apr, path, scratch_pool));

  apr_err = apr_file_remove(path_apr, scratch_pool);

#ifdef WIN32
  /* If the target is read only NTFS reports EACCESS and FAT/FAT32
     reports EEXIST */
  if (APR_STATUS_IS_EACCES(apr_err) || APR_STATUS_IS_EEXIST(apr_err))
    {
      /* Set the destination file writable because Windows will not
         allow us to delete when path is read-only */
      SVN_ERR(svn_io_set_file_read_write(path, ignore_enoent, scratch_pool));
      apr_err = apr_file_remove(path_apr, scratch_pool);
    }

  /* Check to make sure we aren't trying to delete a directory */
  if (apr_err == APR_FROM_OS_ERROR(ERROR_ACCESS_DENIED)
      || apr_err == APR_FROM_OS_ERROR(ERROR_SHARING_VIOLATION))
    {
      apr_finfo_t finfo;

      if (!apr_stat(&finfo, path_apr, APR_FINFO_TYPE, scratch_pool)
          && finfo.filetype == APR_REG)
        {
          WIN32_RETRY_LOOP(apr_err, apr_file_remove(path_apr, scratch_pool));
        }
    }

  /* Just return the delete error */
#endif

  if (!apr_err)
    {
      return SVN_NO_ERROR;
    }
  else if (ignore_enoent && (APR_STATUS_IS_ENOENT(apr_err)
                             || SVN__APR_STATUS_IS_ENOTDIR(apr_err)))
    {
      return SVN_NO_ERROR;
    }
  else
    {
      return svn_error_wrap_apr(apr_err, _("Can't remove file '%s'"),
                                svn_dirent_local_style(path, scratch_pool));
    }
}