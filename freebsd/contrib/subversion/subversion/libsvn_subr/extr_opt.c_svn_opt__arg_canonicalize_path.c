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
typedef  int /*<<< orphan*/  apr_status_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_FILEPATH_TRUENAME ; 
 scalar_t__ APR_STATUS_IS_ENOENT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  apr_filepath_merge (char**,char*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* svn_dirent_canonicalize (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_local_style (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_path_cstring_from_utf8 (char const**,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_path_cstring_to_utf8 (char const**,char const*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_opt__arg_canonicalize_path(const char **path_out, const char *path_in,
                               apr_pool_t *pool)
{
  const char *apr_target;
  char *truenamed_target; /* APR-encoded */
  apr_status_t apr_err;

  /* canonicalize case, and change all separators to '/'. */
  SVN_ERR(svn_path_cstring_from_utf8(&apr_target, path_in, pool));
  apr_err = apr_filepath_merge(&truenamed_target, "", apr_target,
                               APR_FILEPATH_TRUENAME, pool);

  if (!apr_err)
    /* We have a canonicalized APR-encoded target now. */
    apr_target = truenamed_target;
  else if (APR_STATUS_IS_ENOENT(apr_err))
    /* It's okay for the file to not exist, that just means we
       have to accept the case given to the client. We'll use
       the original APR-encoded target. */
    ;
  else
    return svn_error_createf(apr_err, NULL,
                             _("Error resolving case of '%s'"),
                             svn_dirent_local_style(path_in, pool));

  /* convert back to UTF-8. */
  SVN_ERR(svn_path_cstring_to_utf8(path_out, apr_target, pool));
  *path_out = svn_dirent_canonicalize(*path_out, pool);

  return SVN_NO_ERROR;
}