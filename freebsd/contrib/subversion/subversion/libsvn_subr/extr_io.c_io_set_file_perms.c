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
struct TYPE_3__ {scalar_t__ filetype; int protection; } ;
typedef  TYPE_1__ apr_finfo_t ;
typedef  int apr_fileperms_t ;
typedef  int /*<<< orphan*/  apr_fileattrs_t ;

/* Variables and functions */
 scalar_t__ APR_ENOTIMPL ; 
 int /*<<< orphan*/  APR_FILE_ATTR_EXECUTABLE ; 
 int /*<<< orphan*/  APR_FILE_ATTR_READONLY ; 
 int APR_FINFO_LINK ; 
 int APR_FINFO_PROT ; 
 int APR_GEXECUTE ; 
 int APR_GREAD ; 
 int APR_GWRITE ; 
 scalar_t__ APR_LNK ; 
 scalar_t__ APR_STATUS_IS_ENOENT (scalar_t__) ; 
 scalar_t__ APR_STATUS_IS_EPERM (scalar_t__) ; 
 int APR_UEXECUTE ; 
 int APR_UREAD ; 
 int APR_UWRITE ; 
 int APR_WEXECUTE ; 
 int APR_WREAD ; 
 int APR_WWRITE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 scalar_t__ SVN__APR_STATUS_IS_ENOTDIR (scalar_t__) ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ apr_file_attrs_set (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ apr_file_perms_set (char const*,int) ; 
 scalar_t__ apr_stat (TYPE_1__*,char const*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cstring_from_utf8 (char const**,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reown_file (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_local_style (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_wrap_apr (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
io_set_file_perms(const char *path,
                  svn_boolean_t change_readwrite,
                  svn_boolean_t enable_write,
                  svn_boolean_t change_executable,
                  svn_boolean_t executable,
                  svn_boolean_t ignore_enoent,
                  apr_pool_t *pool)
{
  apr_status_t status;
  const char *path_apr;
  apr_finfo_t finfo;
  apr_fileperms_t perms_to_set;

  SVN_ERR(cstring_from_utf8(&path_apr, path, pool));

  /* Try to change only a minimal amount of the perms first
     by getting the current perms and adding bits
     only on where read perms are granted.  If this fails
     fall through to just setting file attributes. */
  status = apr_stat(&finfo, path_apr, APR_FINFO_PROT | APR_FINFO_LINK, pool);
  if (status)
    {
      if (ignore_enoent && (APR_STATUS_IS_ENOENT(status)
                            || SVN__APR_STATUS_IS_ENOTDIR(status)))
        return SVN_NO_ERROR;
      else if (status != APR_ENOTIMPL)
        return svn_error_wrap_apr(status,
                                  _("Can't change perms of file '%s'"),
                                  svn_dirent_local_style(path, pool));
      return SVN_NO_ERROR;
    }

  if (finfo.filetype == APR_LNK)
    return SVN_NO_ERROR;

  perms_to_set = finfo.protection;
  if (change_readwrite)
    {
      if (enable_write) /* Make read-write. */
        {
          /* Tweak the owner bits only. The group/other bits aren't safe to
           * touch because we may end up setting them in undesired ways. */
          perms_to_set |= (APR_UREAD|APR_UWRITE);
        }
      else
        {
          if (finfo.protection & APR_UREAD)
            perms_to_set &= ~APR_UWRITE;
          if (finfo.protection & APR_GREAD)
            perms_to_set &= ~APR_GWRITE;
          if (finfo.protection & APR_WREAD)
            perms_to_set &= ~APR_WWRITE;
        }
    }

  if (change_executable)
    {
      if (executable)
        {
          if (finfo.protection & APR_UREAD)
            perms_to_set |= APR_UEXECUTE;
          if (finfo.protection & APR_GREAD)
            perms_to_set |= APR_GEXECUTE;
          if (finfo.protection & APR_WREAD)
            perms_to_set |= APR_WEXECUTE;
        }
      else
        {
          if (finfo.protection & APR_UREAD)
            perms_to_set &= ~APR_UEXECUTE;
          if (finfo.protection & APR_GREAD)
            perms_to_set &= ~APR_GEXECUTE;
          if (finfo.protection & APR_WREAD)
            perms_to_set &= ~APR_WEXECUTE;
        }
    }

  /* If we aren't changing anything then just return, this saves
     some system calls and helps with shared working copies */
  if (perms_to_set == finfo.protection)
    return SVN_NO_ERROR;

  status = apr_file_perms_set(path_apr, perms_to_set);
  if (!status)
    return SVN_NO_ERROR;

  if (APR_STATUS_IS_EPERM(status))
    {
      /* We don't have permissions to change the
         permissions!  Try a move, copy, and delete
         workaround to see if we can get the file owned by
         us.  If these succeed, try the permissions set
         again.

         Note that we only attempt this in the
         stat-available path.  This assumes that the
         move-copy workaround will only be helpful on
         platforms that implement apr_stat. */
      SVN_ERR(reown_file(path, pool));
      status = apr_file_perms_set(path_apr, perms_to_set);
    }

  if (!status)
    return SVN_NO_ERROR;

  if (ignore_enoent && APR_STATUS_IS_ENOENT(status))
    return SVN_NO_ERROR;
  else if (status == APR_ENOTIMPL)
    {
      /* At least try to set the attributes. */
      apr_fileattrs_t attrs = 0;
      apr_fileattrs_t attrs_values = 0;

      if (change_readwrite)
        {
          attrs = APR_FILE_ATTR_READONLY;
          if (!enable_write)
            attrs_values = APR_FILE_ATTR_READONLY;
        }
      if (change_executable)
        {
          attrs = APR_FILE_ATTR_EXECUTABLE;
          if (executable)
            attrs_values = APR_FILE_ATTR_EXECUTABLE;
        }
      status = apr_file_attrs_set(path_apr, attrs, attrs_values, pool);
    }

  return svn_error_wrap_apr(status,
                            _("Can't change perms of file '%s'"),
                            svn_dirent_local_style(path, pool));
}