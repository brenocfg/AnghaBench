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
struct svn_config_t {int dummy; } ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 char* SVN_CLIENT_EDITOR ; 
 int /*<<< orphan*/  SVN_CONFIG_CATEGORY_CONFIG ; 
 int /*<<< orphan*/  SVN_CONFIG_OPTION_EDITOR_CMD ; 
 int /*<<< orphan*/  SVN_CONFIG_SECTION_HELPERS ; 
 int /*<<< orphan*/  SVN_ERR_CL_NO_EXTERNAL_EDITOR ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  svn_config_get (struct svn_config_t*,char const**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ctype_isspace (char const) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct svn_config_t* svn_hash_gets (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
find_editor_binary(const char **editor,
                   const char *editor_cmd,
                   apr_hash_t *config)
{
  const char *e;
  struct svn_config_t *cfg;

  /* Use the editor specified on the command line via --editor-cmd, if any. */
  e = editor_cmd;

  /* Otherwise look for the Subversion-specific environment variable. */
  if (! e)
    e = getenv("SVN_EDITOR");

  /* If not found then fall back on the config file. */
  if (! e)
    {
      cfg = config ? svn_hash_gets(config, SVN_CONFIG_CATEGORY_CONFIG) : NULL;
      svn_config_get(cfg, &e, SVN_CONFIG_SECTION_HELPERS,
                     SVN_CONFIG_OPTION_EDITOR_CMD, NULL);
    }

  /* If not found yet then try general purpose environment variables. */
  if (! e)
    e = getenv("VISUAL");
  if (! e)
    e = getenv("EDITOR");

#ifdef SVN_CLIENT_EDITOR
  /* If still not found then fall back on the hard-coded default. */
  if (! e)
    e = SVN_CLIENT_EDITOR;
#endif

  /* Error if there is no editor specified */
  if (e)
    {
      const char *c;

      for (c = e; *c; c++)
        if (!svn_ctype_isspace(*c))
          break;

      if (! *c)
        return svn_error_create
          (SVN_ERR_CL_NO_EXTERNAL_EDITOR, NULL,
           _("The EDITOR, SVN_EDITOR or VISUAL environment variable or "
             "'editor-cmd' run-time configuration option is empty or "
             "consists solely of whitespace. Expected a shell command."));
    }
  else
    return svn_error_create
      (SVN_ERR_CL_NO_EXTERNAL_EDITOR, NULL,
       _("None of the environment variables SVN_EDITOR, VISUAL or EDITOR are "
         "set, and no 'editor-cmd' run-time configuration option was found"));

  *editor = e;
  return SVN_NO_ERROR;
}