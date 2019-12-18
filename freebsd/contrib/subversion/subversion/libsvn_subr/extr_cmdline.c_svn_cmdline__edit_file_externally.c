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
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_FILEPATH_NATIVE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_EXTERNAL_PROGRAM ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ apr_filepath_get (char**,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ apr_filepath_set (char const*,int /*<<< orphan*/ *) ; 
 char* apr_psprintf (int /*<<< orphan*/ *,char*,char const*,char const*) ; 
 int /*<<< orphan*/  find_editor_binary (char const**,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  svn_dirent_split (char const**,char const**,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/ * svn_error_wrap_apr (scalar_t__,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  svn_handle_error2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  svn_path_cstring_from_utf8 (char const**,char const*,int /*<<< orphan*/ *) ; 
 int system (char const*) ; 

svn_error_t *
svn_cmdline__edit_file_externally(const char *path,
                                  const char *editor_cmd,
                                  apr_hash_t *config,
                                  apr_pool_t *pool)
{
  const char *editor, *cmd, *base_dir, *file_name, *base_dir_apr;
  char *old_cwd;
  int sys_err;
  apr_status_t apr_err;

  svn_dirent_split(&base_dir, &file_name, path, pool);

  SVN_ERR(find_editor_binary(&editor, editor_cmd, config));

  apr_err = apr_filepath_get(&old_cwd, APR_FILEPATH_NATIVE, pool);
  if (apr_err)
    return svn_error_wrap_apr(apr_err, _("Can't get working directory"));

  /* APR doesn't like "" directories */
  if (base_dir[0] == '\0')
    base_dir_apr = ".";
  else
    SVN_ERR(svn_path_cstring_from_utf8(&base_dir_apr, base_dir, pool));

  apr_err = apr_filepath_set(base_dir_apr, pool);
  if (apr_err)
    return svn_error_wrap_apr
      (apr_err, _("Can't change working directory to '%s'"), base_dir);

  cmd = apr_psprintf(pool, "%s %s", editor, file_name);
  sys_err = system(cmd);

  apr_err = apr_filepath_set(old_cwd, pool);
  if (apr_err)
    svn_handle_error2(svn_error_wrap_apr
                      (apr_err, _("Can't restore working directory")),
                      stderr, TRUE /* fatal */, "svn: ");

  if (sys_err)
    /* Extracting any meaning from sys_err is platform specific, so just
       use the raw value. */
    return svn_error_createf(SVN_ERR_EXTERNAL_PROGRAM, NULL,
                             _("system('%s') returned %d"), cmd, sys_err);

  return SVN_NO_ERROR;
}