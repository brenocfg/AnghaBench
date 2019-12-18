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
struct mi_opt {char* member_0; int member_1; int /*<<< orphan*/  member_2; } ;
typedef  enum opt { ____Placeholder_opt } opt ;
typedef  enum mi_cmd_result { ____Placeholder_mi_cmd_result } mi_cmd_result ;

/* Variables and functions */
 int MI_CMD_DONE ; 
 int /*<<< orphan*/  dont_repeat () ; 
 int /*<<< orphan*/  env_execute_cli_command (char*,char*) ; 
 int /*<<< orphan*/  env_mod_path (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  forget_cached_source_info () ; 
 int /*<<< orphan*/  init_last_source_visited () ; 
 int /*<<< orphan*/  init_source_path () ; 
 int mi_getopt (char*,int,char**,struct mi_opt*,int*,char**) ; 
 int mi_version (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  source_path ; 
 int /*<<< orphan*/  ui_out_field_string (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiout ; 
 int /*<<< orphan*/  xfree (int /*<<< orphan*/ ) ; 

enum mi_cmd_result
mi_cmd_env_dir (char *command, char **argv, int argc)
{
  int i;
  int optind = 0;
  int reset = 0;
  char *optarg;
  enum opt
    {
      RESET_OPT
    };
  static struct mi_opt opts[] =
  {
    {"r", RESET_OPT, 0},
    0
  };

  dont_repeat ();

  if (mi_version (uiout) < 2)
    {
      for (i = argc - 1; i >= 0; --i)
	env_execute_cli_command ("dir", argv[i]);
      return MI_CMD_DONE;
    }

  /* Otherwise mi level is 2 or higher.  */
  while (1)
    {
      int opt = mi_getopt ("mi_cmd_env_dir", argc, argv, opts,
                           &optind, &optarg);
      if (opt < 0)
        break;
      switch ((enum opt) opt)
        {
        case RESET_OPT:
          reset = 1;
          break;
        }
    }
  argv += optind;
  argc -= optind;

  if (reset)
    {
      /* Reset means setting to default path first.  */
      xfree (source_path);
      init_source_path ();
    }

  for (i = argc - 1; i >= 0; --i)
    env_mod_path (argv[i], &source_path);
  init_last_source_visited ();

  ui_out_field_string (uiout, "source-path", source_path);
  forget_cached_source_info ();

  return MI_CMD_DONE;
}