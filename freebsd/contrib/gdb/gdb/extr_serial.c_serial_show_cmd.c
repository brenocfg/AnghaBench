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

/* Variables and functions */
 int /*<<< orphan*/  cmd_show_list (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  serial_show_cmdlist ; 

__attribute__((used)) static void
serial_show_cmd (char *args, int from_tty)
{
  cmd_show_list (serial_show_cmdlist, from_tty, "");
}