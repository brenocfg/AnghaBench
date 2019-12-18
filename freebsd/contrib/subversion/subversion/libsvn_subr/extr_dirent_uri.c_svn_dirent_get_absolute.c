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
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ apr_status_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_FILEPATH_NOTRELATIVE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int) ; 
 int /*<<< orphan*/  SVN_ERR_BAD_FILENAME ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ apr_filepath_merge (char**,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* apr_pstrdup (int /*<<< orphan*/ *,char const*) ; 
 char* svn_dirent_canonicalize (char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_dirent_is_absolute (char const*) ; 
 scalar_t__ svn_dirent_is_canonical (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_local_style (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_create (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_path_cstring_from_utf8 (char const**,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_path_cstring_to_utf8 (char const**,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_path_is_backpath_present (char const*) ; 
 int /*<<< orphan*/  svn_path_is_url (char const*) ; 

svn_error_t *
svn_dirent_get_absolute(const char **pabsolute,
                        const char *relative,
                        apr_pool_t *pool)
{
  char *buffer;
  apr_status_t apr_err;
  const char *path_apr;

  SVN_ERR_ASSERT(! svn_path_is_url(relative));

  /* Merge the current working directory with the relative dirent. */
  SVN_ERR(svn_path_cstring_from_utf8(&path_apr, relative, pool));

  apr_err = apr_filepath_merge(&buffer, NULL,
                               path_apr,
                               APR_FILEPATH_NOTRELATIVE,
                               pool);
  if (apr_err)
    {
      /* In some cases when the passed path or its ancestor(s) do not exist
         or no longer exist apr returns an error.

         In many of these cases we would like to return a path anyway, when the
         passed path was already a safe absolute path. So check for that now to
         avoid an error.

         svn_dirent_is_absolute() doesn't perform the necessary checks to see
         if the path doesn't need post processing to be in the canonical absolute
         format.
         */

      if (svn_dirent_is_absolute(relative)
          && svn_dirent_is_canonical(relative, pool)
          && !svn_path_is_backpath_present(relative))
        {
          *pabsolute = apr_pstrdup(pool, relative);
          return SVN_NO_ERROR;
        }

      return svn_error_createf(SVN_ERR_BAD_FILENAME,
                               svn_error_create(apr_err, NULL, NULL),
                               _("Couldn't determine absolute path of '%s'"),
                               svn_dirent_local_style(relative, pool));
    }

  SVN_ERR(svn_path_cstring_to_utf8(pabsolute, buffer, pool));
  *pabsolute = svn_dirent_canonicalize(*pabsolute, pool);
  return SVN_NO_ERROR;
}