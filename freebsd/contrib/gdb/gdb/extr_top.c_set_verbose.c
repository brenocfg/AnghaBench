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
struct cmd_list_element {char* doc; } ;

/* Variables and functions */
 scalar_t__ info_verbose ; 
 struct cmd_list_element* lookup_cmd_1 (char**,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  showlist ; 

void
set_verbose (char *args, int from_tty, struct cmd_list_element *c)
{
  char *cmdname = "verbose";
  struct cmd_list_element *showcmd;

  showcmd = lookup_cmd_1 (&cmdname, showlist, NULL, 1);

  if (info_verbose)
    {
      c->doc = "Set verbose printing of informational messages.";
      showcmd->doc = "Show verbose printing of informational messages.";
    }
  else
    {
      c->doc = "Set verbosity.";
      showcmd->doc = "Show verbosity.";
    }
}