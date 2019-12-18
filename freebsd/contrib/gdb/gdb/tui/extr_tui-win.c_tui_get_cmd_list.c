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
struct cmd_list_element {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_prefix_cmd (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  class_tui ; 
 int /*<<< orphan*/  cmdlist ; 
 int /*<<< orphan*/  tui_command ; 
 scalar_t__ tuilist ; 

struct cmd_list_element **
tui_get_cmd_list ()
{
  if (tuilist == 0)
    add_prefix_cmd ("tui", class_tui, tui_command,
                    "Text User Interface commands.",
                    &tuilist, "tui ", 0, &cmdlist);
  return &tuilist;
}