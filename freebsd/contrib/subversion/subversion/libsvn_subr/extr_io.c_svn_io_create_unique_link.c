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
typedef  scalar_t__ apr_status_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_3__ {scalar_t__ filetype; } ;
typedef  TYPE_1__ apr_finfo_t ;

/* Variables and functions */
 scalar_t__ APR_DIR ; 
 int /*<<< orphan*/  APR_FINFO_TYPE ; 
 scalar_t__ APR_STATUS_IS_EACCES (scalar_t__) ; 
 scalar_t__ APR_STATUS_IS_EEXIST (scalar_t__) ; 
 scalar_t__ APR_STATUS_IS_EINTR (scalar_t__) ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_IO_UNIQUE_NAMES_EXHAUSTED ; 
 int /*<<< orphan*/  SVN_ERR_UNSUPPORTED_FEATURE ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ apr_get_os_error () ; 
 char* apr_psprintf (int /*<<< orphan*/ *,char*,char const*,...) ; 
 scalar_t__ apr_stat (TYPE_1__*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cstring_from_utf8 (char const**,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_local_style (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_wrap_apr (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int symlink (char const*,char const*) ; 

svn_error_t *
svn_io_create_unique_link(const char **unique_name_p,
                          const char *path,
                          const char *dest,
                          const char *suffix,
                          apr_pool_t *pool)
{
#ifdef HAVE_SYMLINK
  unsigned int i;
  const char *unique_name;
  const char *unique_name_apr;
  const char *dest_apr;
  int rv;

  SVN_ERR(cstring_from_utf8(&dest_apr, dest, pool));
  for (i = 1; i <= 99999; i++)
    {
      apr_status_t apr_err;

      /* Special case the first attempt -- if we can avoid having a
         generated numeric portion at all, that's best.  So first we
         try with just the suffix; then future tries add a number
         before the suffix.  (A do-while loop could avoid the repeated
         conditional, but it's not worth the clarity loss.)

         If the first attempt fails, the first number will be "2".
         This is good, since "1" would misleadingly imply that
         the second attempt was actually the first... and if someone's
         got conflicts on their conflicts, we probably don't want to
         add to their confusion :-). */
      if (i == 1)
        unique_name = apr_psprintf(pool, "%s%s", path, suffix);
      else
        unique_name = apr_psprintf(pool, "%s.%u%s", path, i, suffix);

      /* Hmmm.  Ideally, we would append to a native-encoding buf
         before starting iteration, then convert back to UTF-8 for
         return. But I suppose that would make the appending code
         sensitive to i18n in a way it shouldn't be... Oh well. */
      SVN_ERR(cstring_from_utf8(&unique_name_apr, unique_name, pool));
      do {
        rv = symlink(dest_apr, unique_name_apr);
      } while (rv == -1 && APR_STATUS_IS_EINTR(apr_get_os_error()));

      apr_err = apr_get_os_error();

      if (rv == -1 && APR_STATUS_IS_EEXIST(apr_err))
        continue;
      else if (rv == -1 && apr_err)
        {
          /* On Win32, CreateFile fails with an "Access Denied" error
             code, rather than "File Already Exists", if the colliding
             name belongs to a directory. */
          if (APR_STATUS_IS_EACCES(apr_err))
            {
              apr_finfo_t finfo;
              apr_status_t apr_err_2 = apr_stat(&finfo, unique_name_apr,
                                                APR_FINFO_TYPE, pool);

              if (!apr_err_2
                  && (finfo.filetype == APR_DIR))
                continue;

              /* Else ignore apr_err_2; better to fall through and
                 return the original error. */
            }

          *unique_name_p = NULL;
          return svn_error_wrap_apr(apr_err,
                                    _("Can't create symbolic link '%s'"),
                                    svn_dirent_local_style(unique_name, pool));
        }
      else
        {
          *unique_name_p = unique_name;
          return SVN_NO_ERROR;
        }
    }

  *unique_name_p = NULL;
  return svn_error_createf(SVN_ERR_IO_UNIQUE_NAMES_EXHAUSTED,
                           NULL,
                           _("Unable to make name for '%s'"),
                           svn_dirent_local_style(path, pool));
#else
  return svn_error_create(SVN_ERR_UNSUPPORTED_FEATURE, NULL,
                          _("Symbolic links are not supported on this "
                            "platform"));
#endif
}