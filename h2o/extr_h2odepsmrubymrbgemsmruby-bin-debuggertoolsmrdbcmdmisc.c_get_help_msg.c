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
struct TYPE_4__ {int /*<<< orphan*/ * cmd2; int /*<<< orphan*/ * cmd1; } ;
typedef  TYPE_1__ help_msg ;

/* Variables and functions */
 scalar_t__ check_cmd_pattern (int /*<<< orphan*/ *,char*) ; 
 TYPE_1__* help_msg_list ; 

__attribute__((used)) static help_msg*
get_help_msg(char *cmd1, char *cmd2)
{
  help_msg *p;

  if (cmd1 == NULL) {
    return NULL;
  }
  for (p = help_msg_list; p->cmd1 != NULL; p++) {
    if (check_cmd_pattern(p->cmd1, cmd1) && check_cmd_pattern(p->cmd2, cmd2)) {
      return p;
    }
  }
  return NULL;
}