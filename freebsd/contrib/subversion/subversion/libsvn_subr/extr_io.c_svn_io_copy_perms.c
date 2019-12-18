#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_node_kind_t ;
struct TYPE_10__ {int /*<<< orphan*/  apr_err; } ;
typedef  TYPE_1__ svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_11__ {int /*<<< orphan*/  protection; } ;
typedef  TYPE_2__ apr_finfo_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_FINFO_PROT ; 
 scalar_t__ APR_STATUS_IS_ENOTIMPL (int /*<<< orphan*/ ) ; 
 scalar_t__ APR_STATUS_IS_INCOMPLETE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 TYPE_1__* SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 TYPE_1__* file_perms_set (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_local_style (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_1__*) ; 
 TYPE_1__* svn_error_quick_wrapf (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_io_check_special_path (char const*,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_stat (TYPE_2__*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_io_copy_perms(const char *src,
                  const char *dst,
                  apr_pool_t *pool)
{
  /* ### On Windows or OS/2, apr_file_perms_set always returns APR_ENOTIMPL,
         and the path passed to apr_file_perms_set must be encoded
         in the platform-specific path encoding; not necessary UTF-8.
         We need a platform-specific implementation to get the
         permissions right. */

#if !defined(WIN32) && !defined(__OS2__)
  {
    apr_finfo_t finfo;
    svn_node_kind_t kind;
    svn_boolean_t is_special;
    svn_error_t *err;

    /* If DST is a symlink, don't bother copying permissions. */
    SVN_ERR(svn_io_check_special_path(dst, &kind, &is_special, pool));
    if (is_special)
      return SVN_NO_ERROR;

    SVN_ERR(svn_io_stat(&finfo, src, APR_FINFO_PROT, pool));
    err = file_perms_set(dst, finfo.protection, pool);
    if (err)
      {
        /* We shouldn't be able to get APR_INCOMPLETE or APR_ENOTIMPL
           here under normal circumstances, because the perms themselves
           came from a call to apr_file_info_get(), and we already know
           this is the non-Win32 case.  But if it does happen, it's not
           an error. */
        if (APR_STATUS_IS_INCOMPLETE(err->apr_err) ||
            APR_STATUS_IS_ENOTIMPL(err->apr_err))
          svn_error_clear(err);
        else
          {
            return svn_error_quick_wrapf(
                     err, _("Can't set permissions on '%s'"),
                     svn_dirent_local_style(dst, pool));
          }
      }
  }
#endif /* !WIN32 && !__OS2__ */

  return SVN_NO_ERROR;
}