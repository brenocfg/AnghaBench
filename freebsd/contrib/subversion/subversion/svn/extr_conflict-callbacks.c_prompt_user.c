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
typedef  int /*<<< orphan*/  client_option_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/ * find_option (int /*<<< orphan*/  const*,char const*) ; 
 int /*<<< orphan*/  help_string (char const**,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 char* prompt_string (int /*<<< orphan*/  const*,char const* const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  svn_cmdline_fprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  svn_cmdline_prompt_user2 (char const**,char const*,void*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
prompt_user(const client_option_t **opt,
            const apr_array_header_t *conflict_options,
            const char *const *options_to_show,
            const char *conflict_description,
            void *prompt_baton,
            apr_pool_t *scratch_pool)
{
  const char *prompt
    = prompt_string(conflict_options, options_to_show, scratch_pool);
  const char *answer;

  SVN_ERR(svn_cmdline_prompt_user2(&answer, prompt, prompt_baton, scratch_pool));
  if (strcmp(answer, "h") == 0 || strcmp(answer, "?") == 0)
    {
      const char *helpstr;

      if (conflict_description)
        SVN_ERR(svn_cmdline_fprintf(stderr, scratch_pool, "\n%s\n",
                                    conflict_description));
      SVN_ERR(help_string(&helpstr, conflict_options, scratch_pool));
      SVN_ERR(svn_cmdline_fprintf(stderr, scratch_pool, "\n%s\n", helpstr));
      *opt = NULL;
    }
  else
    {
      *opt = find_option(conflict_options, answer);
      if (! *opt)
        {
          SVN_ERR(svn_cmdline_fprintf(stderr, scratch_pool,
                                      _("Unrecognized option.\n\n")));
        }
    }
  return SVN_NO_ERROR;
}