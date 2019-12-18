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
struct TYPE_3__ {int /*<<< orphan*/ * error; int /*<<< orphan*/ * arg; } ;
typedef  TYPE_1__ cli_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  JERRY_LOG_LEVEL_ERROR ; 
 int /*<<< orphan*/  jerry_port_log (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,...) ; 

__attribute__((used)) static bool
check_cli_error (const cli_state_t *const cli_state_p)
{
  if (cli_state_p->error != NULL)
  {
    if (cli_state_p->arg != NULL)
    {
      jerry_port_log (JERRY_LOG_LEVEL_ERROR, "Error: %s %s\n", cli_state_p->error, cli_state_p->arg);
    }
    else
    {
      jerry_port_log (JERRY_LOG_LEVEL_ERROR, "Error: %s\n", cli_state_p->error);
    }

    return true;
  }

  return false;
}