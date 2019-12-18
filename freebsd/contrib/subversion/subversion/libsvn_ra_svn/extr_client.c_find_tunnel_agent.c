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
typedef  int /*<<< orphan*/  svn_config_t ;
typedef  scalar_t__ apr_status_t ;
typedef  int apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 scalar_t__ APR_SUCCESS ; 
 int /*<<< orphan*/  SVN_CONFIG_CATEGORY_CONFIG ; 
 int /*<<< orphan*/  SVN_CONFIG_SECTION_TUNNELS ; 
 int /*<<< orphan*/  SVN_ERR_BAD_URL ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 char** apr_palloc (int /*<<< orphan*/ *,int) ; 
 char* apr_pstrmemdup (int /*<<< orphan*/ *,char const*,int) ; 
 scalar_t__ apr_tokenize_to_argv (char const*,char***,int /*<<< orphan*/ *) ; 
 char* getenv (char const*) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int strcspn (char const*,char*) ; 
 int /*<<< orphan*/  svn_config_get (int /*<<< orphan*/ *,char const**,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,...) ; 
 int /*<<< orphan*/ * svn_error_wrap_apr (scalar_t__,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/ * svn_hash_gets (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *find_tunnel_agent(const char *tunnel,
                                      const char *hostinfo,
                                      const char ***argv_p,
                                      apr_hash_t *config, apr_pool_t *pool)
{
  svn_config_t *cfg;
  const char *val, *var, *cmd;
  char **cmd_argv;
  const char **argv;
  apr_size_t len;
  apr_status_t status;
  int n;

  /* Look up the tunnel specification in config. */
  cfg = config ? svn_hash_gets(config, SVN_CONFIG_CATEGORY_CONFIG) : NULL;
  svn_config_get(cfg, &val, SVN_CONFIG_SECTION_TUNNELS, tunnel, NULL);

  /* We have one predefined tunnel scheme, if it isn't overridden by config. */
  if (!val && strcmp(tunnel, "ssh") == 0)
    {
      /* Killing the tunnel agent with SIGTERM leads to unsightly
       * stderr output from ssh, unless we pass -q.
       * The "-q" option to ssh is widely supported: all versions of
       * OpenSSH have it, the old ssh-1.x and the 2.x, 3.x ssh.com
       * versions have it too. If the user is using some other ssh
       * implementation that doesn't accept it, they can override it
       * in the [tunnels] section of the config. */
      val = "$SVN_SSH ssh -q --";
    }

  if (!val || !*val)
    return svn_error_createf(SVN_ERR_BAD_URL, NULL,
                             _("Undefined tunnel scheme '%s'"), tunnel);

  /* If the scheme definition begins with "$varname", it means there
   * is an environment variable which can override the command. */
  if (*val == '$')
    {
      val++;
      len = strcspn(val, " ");
      var = apr_pstrmemdup(pool, val, len);
      cmd = getenv(var);
      if (!cmd)
        {
          cmd = val + len;
          while (*cmd == ' ')
            cmd++;
          if (!*cmd)
            return svn_error_createf(SVN_ERR_BAD_URL, NULL,
                                     _("Tunnel scheme %s requires environment "
                                       "variable %s to be defined"), tunnel,
                                     var);
        }
    }
  else
    cmd = val;

  /* Tokenize the command into a list of arguments. */
  status = apr_tokenize_to_argv(cmd, &cmd_argv, pool);
  if (status != APR_SUCCESS)
    return svn_error_wrap_apr(status, _("Can't tokenize command '%s'"), cmd);

  /* Calc number of the fixed arguments. */
  for (n = 0; cmd_argv[n] != NULL; n++)
    ;

  argv = apr_palloc(pool, (n + 4) * sizeof(char *));

  /* Append the fixed arguments to the result. */
  for (n = 0; cmd_argv[n] != NULL; n++)
    argv[n] = cmd_argv[n];

  argv[n++] = hostinfo;
  argv[n++] = "svnserve";
  argv[n++] = "-t";
  argv[n] = NULL;

  *argv_p = argv;
  return SVN_NO_ERROR;
}