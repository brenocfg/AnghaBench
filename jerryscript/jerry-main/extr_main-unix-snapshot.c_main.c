#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {char* error; } ;
typedef  TYPE_1__ cli_state_t ;

/* Variables and functions */
#define  CLI_OPT_DEFAULT 129 
 int CLI_OPT_END ; 
 int /*<<< orphan*/  JERRY_LOG_LEVEL_ERROR ; 
 int JERRY_STANDALONE_EXIT_CODE_FAIL ; 
 int JERRY_STANDALONE_EXIT_CODE_OK ; 
#define  OPT_MERGE_HELP 128 
 scalar_t__ check_cli_error (TYPE_1__*) ; 
 int cli_consume_option (TYPE_1__*) ; 
 char* cli_consume_string (TYPE_1__*) ; 
 TYPE_1__ cli_init (int /*<<< orphan*/ ,int,char**) ; 
 int /*<<< orphan*/  jerry_port_log (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  main_opts ; 
 int /*<<< orphan*/  print_commands (char*) ; 
 int process_generate (TYPE_1__*,int,char*) ; 
 int process_literal_dump (TYPE_1__*,int,char*) ; 
 int process_merge (TYPE_1__*,int,char*) ; 
 int /*<<< orphan*/  strcmp (char*,char const*) ; 

int
main (int argc, /**< number of arguments */
      char **argv) /**< argument list */
{
  cli_state_t cli_state = cli_init (main_opts, argc - 1, argv + 1);

  for (int id = cli_consume_option (&cli_state); id != CLI_OPT_END; id = cli_consume_option (&cli_state))
  {
    switch (id)
    {
      case OPT_MERGE_HELP:
      {
        /* Help is always printed if no command is provided. */
        break;
      }
      case CLI_OPT_DEFAULT:
      {
        const char *command_p = cli_consume_string (&cli_state);

        if (cli_state.error != NULL)
        {
          break;
        }

        if (!strcmp ("merge", command_p))
        {
          return process_merge (&cli_state, argc, argv[0]);
        }
        else if (!strcmp ("litdump", command_p))
        {
          return process_literal_dump (&cli_state, argc, argv[0]);
        }
        else if (!strcmp ("generate", command_p))
        {
          return process_generate (&cli_state, argc, argv[0]);
        }

        jerry_port_log (JERRY_LOG_LEVEL_ERROR, "Error: unknown command: %s\n\n", command_p);
        print_commands (argv[0]);

        return JERRY_STANDALONE_EXIT_CODE_FAIL;
      }
      default:
      {
        cli_state.error = "Internal error";
        break;
      }
    }
  }

  if (check_cli_error (&cli_state))
  {
    return JERRY_STANDALONE_EXIT_CODE_FAIL;
  }

  print_commands (argv[0]);
  return JERRY_STANDALONE_EXIT_CODE_OK;
}