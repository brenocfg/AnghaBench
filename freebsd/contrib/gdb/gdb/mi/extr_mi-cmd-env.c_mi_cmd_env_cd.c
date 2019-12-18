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
typedef  enum mi_cmd_result { ____Placeholder_mi_cmd_result } mi_cmd_result ;

/* Variables and functions */
 int MI_CMD_DONE ; 
 int /*<<< orphan*/  env_execute_cli_command (char*,char*) ; 
 int /*<<< orphan*/  error (char*) ; 

enum mi_cmd_result
mi_cmd_env_cd (char *command, char **argv, int argc)
{
  if (argc == 0 || argc > 1)
    error ("mi_cmd_env_cd: Usage DIRECTORY");
          
  env_execute_cli_command ("cd", argv[0]);

  return MI_CMD_DONE;
}