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
struct TYPE_3__ {scalar_t__ id; char* opt; char* longopt; char* meta; } ;
typedef  TYPE_1__ cli_opt_t ;

/* Variables and functions */
 int CLI_LINE_INDENT ; 
 int CLI_LINE_LENGTH ; 
 scalar_t__ CLI_OPT_DEFAULT ; 
 int /*<<< orphan*/  cli_print_pad (int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static void
cli_opt_usage (const char *prog_name_p, /**< program name, typically argv[0] */
               const char *command_name_p, /**< command name if available */
               const cli_opt_t *opts_p) /**< array of command line option definitions, terminated by CLI_OPT_DEFAULT */
{
  int length = (int) strlen (prog_name_p);
  const cli_opt_t *current_opt_p = opts_p;

  printf ("%s", prog_name_p);

  if (command_name_p != NULL)
  {
    int command_length = (int) strlen (command_name_p);

    if (length + 1 + command_length > CLI_LINE_LENGTH)
    {
      length = CLI_LINE_INDENT - 1;
      printf ("\n");
      cli_print_pad (length);
    }

    printf (" %s", command_name_p);
  }

  while (current_opt_p->id != CLI_OPT_DEFAULT)
  {
    const char *opt_p = current_opt_p->opt;
    int opt_length = 2 + 1;

    if (opt_p == NULL)
    {
      opt_p = current_opt_p->longopt;
      opt_length++;
    }

    opt_length += (int) strlen (opt_p);

    if (length + 1 + opt_length >= CLI_LINE_LENGTH)
    {
      length = CLI_LINE_INDENT - 1;
      printf ("\n");
      cli_print_pad (length);
    }
    length += opt_length;

    printf (" [");

    if (current_opt_p->opt != NULL)
    {
      printf ("-%s", opt_p);
    }
    else
    {
      printf ("--%s", opt_p);
    }

    if (current_opt_p->meta != NULL)
    {
      printf (" %s", current_opt_p->meta);
    }

    printf ("]");

    current_opt_p++;
  }

  if (current_opt_p->meta != NULL)
  {
    const char *opt_p = current_opt_p->meta;
    int opt_length = (int) (2 + strlen (opt_p));

    if (length + 1 + opt_length >= CLI_LINE_LENGTH)
    {
      length = CLI_LINE_INDENT - 1;
      printf ("\n");
      cli_print_pad (length);
    }

    printf (" [%s]", opt_p);
  }

  printf ("\n\n");
}