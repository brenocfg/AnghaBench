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
typedef  int svn_boolean_t ;
struct svn_config_t {int dummy; } ;
typedef  scalar_t__ apr_status_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_FILEPATH_NATIVE ; 
 scalar_t__ APR_SUCCESS ; 
 int /*<<< orphan*/  SVN_CONFIG_CATEGORY_CONFIG ; 
 int /*<<< orphan*/  SVN_CONFIG_OPTION_MERGE_TOOL_CMD ; 
 int /*<<< orphan*/  SVN_CONFIG_SECTION_HELPERS ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_CL_NO_EXTERNAL_MERGE_TOOL ; 
 int /*<<< orphan*/  SVN_ERR_EXTERNAL_PROGRAM ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ apr_env_get (char**,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ apr_filepath_get (char**,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_config_get (struct svn_config_t*,char const**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ctype_isspace (char const) ; 
 int /*<<< orphan*/  svn_dirent_internal_style (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/ * svn_error_wrap_apr (scalar_t__,int /*<<< orphan*/ *) ; 
 struct svn_config_t* svn_hash_gets (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_io_run_cmd (int /*<<< orphan*/ ,char*,char const**,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_cl__merge_file_externally(const char *base_path,
                              const char *their_path,
                              const char *my_path,
                              const char *merged_path,
                              const char *wc_path,
                              apr_hash_t *config,
                              svn_boolean_t *remains_in_conflict,
                              apr_pool_t *pool)
{
  char *merge_tool;
  /* Error if there is no editor specified */
  if (apr_env_get(&merge_tool, "SVN_MERGE", pool) != APR_SUCCESS)
    {
      struct svn_config_t *cfg;
      merge_tool = NULL;
      cfg = config ? svn_hash_gets(config, SVN_CONFIG_CATEGORY_CONFIG) : NULL;
      /* apr_env_get wants char **, this wants const char ** */
      svn_config_get(cfg, (const char **)&merge_tool,
                     SVN_CONFIG_SECTION_HELPERS,
                     SVN_CONFIG_OPTION_MERGE_TOOL_CMD, NULL);
    }

  if (merge_tool)
    {
      const char *c;

      for (c = merge_tool; *c; c++)
        if (!svn_ctype_isspace(*c))
          break;

      if (! *c)
        return svn_error_create
          (SVN_ERR_CL_NO_EXTERNAL_MERGE_TOOL, NULL,
           _("The SVN_MERGE environment variable is empty or "
             "consists solely of whitespace. Expected a shell command.\n"));
    }
  else
      return svn_error_create
        (SVN_ERR_CL_NO_EXTERNAL_MERGE_TOOL, NULL,
         _("The environment variable SVN_MERGE and the merge-tool-cmd run-time "
           "configuration option were not set.\n"));

  {
    const char *arguments[7] = { 0 };
    char *cwd;
    int exitcode;

    apr_status_t status = apr_filepath_get(&cwd, APR_FILEPATH_NATIVE, pool);
    if (status != 0)
      return svn_error_wrap_apr(status, NULL);

    arguments[0] = merge_tool;
    arguments[1] = base_path;
    arguments[2] = their_path;
    arguments[3] = my_path;
    arguments[4] = merged_path;
    arguments[5] = wc_path;
    arguments[6] = NULL;

    SVN_ERR(svn_io_run_cmd(svn_dirent_internal_style(cwd, pool), merge_tool,
                           arguments, &exitcode, NULL, TRUE, NULL, NULL, NULL,
                           pool));
    /* Exit code 0 means the merge was successful.
     * Exit code 1 means the file was left in conflict but it
     * is OK to continue with the merge.
     * Any other exit code means there was a real problem. */
    if (exitcode != 0 && exitcode != 1)
      return svn_error_createf(SVN_ERR_EXTERNAL_PROGRAM, NULL,
        _("The external merge tool '%s' exited with exit code %d."),
        merge_tool, exitcode);
    else if (remains_in_conflict)
      *remains_in_conflict = exitcode == 1;
  }
  return SVN_NO_ERROR;
}