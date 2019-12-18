#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {char* name; char** aliases; char* help; scalar_t__* valid_options; } ;
typedef  TYPE_1__ svn_opt_subcommand_desc_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  size_t apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_9__ {scalar_t__ description; } ;
typedef  TYPE_2__ apr_getopt_option_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 size_t SVN_OPT_MAX_ALIASES ; 
 size_t SVN_OPT_MAX_OPTIONS ; 
 scalar_t__ TRUE ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  svn_cmdline_fprintf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  svn_cmdline_fputs (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_opt_format_option (char const**,TYPE_2__ const*,scalar_t__,int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_opt_get_option_from_code2 (scalar_t__,TYPE_2__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
print_command_info(const svn_opt_subcommand_desc_t *cmd,
                   const apr_getopt_option_t *options_table,
                   svn_boolean_t help,
                   apr_pool_t *pool,
                   FILE *stream)
{
  svn_boolean_t first_time;
  apr_size_t i;

  /* Print the canonical command name. */
  SVN_ERR(svn_cmdline_fputs(cmd->name, stream, pool));

  /* Print the list of aliases. */
  first_time = TRUE;
  for (i = 0; i < SVN_OPT_MAX_ALIASES; i++)
    {
      if (cmd->aliases[i] == NULL)
        break;

      if (first_time) {
        SVN_ERR(svn_cmdline_fputs(" (", stream, pool));
        first_time = FALSE;
      }
      else
        SVN_ERR(svn_cmdline_fputs(", ", stream, pool));

      SVN_ERR(svn_cmdline_fputs(cmd->aliases[i], stream, pool));
    }

  if (! first_time)
    SVN_ERR(svn_cmdline_fputs(")", stream, pool));

  if (help)
    {
      const apr_getopt_option_t *option;
      svn_boolean_t have_options = FALSE;

      SVN_ERR(svn_cmdline_fprintf(stream, pool, ": %s", _(cmd->help)));

      /* Loop over all valid option codes attached to the subcommand */
      for (i = 0; i < SVN_OPT_MAX_OPTIONS; i++)
        {
          if (cmd->valid_options[i])
            {
              if (!have_options)
                {
                  SVN_ERR(svn_cmdline_fputs(_("\nValid options:\n"),
                                            stream, pool));
                  have_options = TRUE;
                }

              /* convert each option code into an option */
              option =
                svn_opt_get_option_from_code2(cmd->valid_options[i],
                                              options_table, NULL, pool);

              /* print the option's docstring */
              if (option && option->description)
                {
                  const char *optstr;
                  svn_opt_format_option(&optstr, option, TRUE, pool);
                  SVN_ERR(svn_cmdline_fprintf(stream, pool, "  %s\n",
                                              optstr));
                }
            }
        }

      if (have_options)
        SVN_ERR(svn_cmdline_fprintf(stream, pool, "\n"));
    }

  return SVN_NO_ERROR;
}