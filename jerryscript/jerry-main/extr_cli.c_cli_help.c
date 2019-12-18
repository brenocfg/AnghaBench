#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ id; char* opt; char* longopt; char* meta; int /*<<< orphan*/ * help; } ;
typedef  TYPE_1__ cli_opt_t ;

/* Variables and functions */
 int CLI_LINE_INDENT ; 
 int CLI_LINE_TAB ; 
 scalar_t__ CLI_OPT_DEFAULT ; 
 int /*<<< orphan*/  cli_opt_usage (char const*,char const*,TYPE_1__ const*) ; 
 int /*<<< orphan*/  cli_print_help (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cli_print_pad (int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ strlen (char*) ; 

void
cli_help (const char *prog_name_p, /**< program name, typically argv[0] */
          const char *command_name_p, /**< command name if available */
          const cli_opt_t *options_p) /**< array of command line option definitions, terminated by CLI_OPT_DEFAULT */
{
  cli_opt_usage (prog_name_p, command_name_p, options_p);

  const cli_opt_t *opt_p = options_p;

  while (opt_p->id != CLI_OPT_DEFAULT)
  {
    int length = CLI_LINE_INDENT;
    cli_print_pad (CLI_LINE_INDENT);

    if (opt_p->opt != NULL)
    {
      printf ("-%s", opt_p->opt);
      length += (int) (strlen (opt_p->opt) + 1);
    }

    if (opt_p->opt != NULL && opt_p->longopt != NULL)
    {
      printf (", ");
      length += 2;
    }

    if (opt_p->longopt != NULL)
    {
      printf ("--%s", opt_p->longopt);
      length += (int) (strlen (opt_p->longopt) + 2);
    }

    if (opt_p->meta != NULL)
    {
      printf (" %s", opt_p->meta);
      length += 1 + (int) strlen (opt_p->meta);
    }

    if (opt_p->help != NULL)
    {
      if (length >= CLI_LINE_TAB)
      {
        printf ("\n");
        length = 0;
      }
      cli_print_pad (CLI_LINE_TAB - length);
      length = CLI_LINE_TAB;

      cli_print_help (opt_p->help);
    }

    printf ("\n");
    opt_p++;
  }

  if (opt_p->help != NULL)
  {
    int length = 0;

    if (opt_p->meta != NULL)
    {
      length = (int) (CLI_LINE_INDENT + strlen (opt_p->meta));

      cli_print_pad (CLI_LINE_INDENT);
      printf ("%s", opt_p->meta);
    }

    if (length >= CLI_LINE_TAB)
    {
      printf ("\n");
      length = 0;
    }

    cli_print_pad (CLI_LINE_TAB - length);

    cli_print_help (opt_p->help);
    printf ("\n");
  }
}