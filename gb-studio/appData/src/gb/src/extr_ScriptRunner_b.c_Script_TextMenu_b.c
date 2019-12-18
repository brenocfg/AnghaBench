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
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  UIShowMenu (int,int,int,int) ; 
 int /*<<< orphan*/  script_action_complete ; 
 int* script_cmd_args ; 
 scalar_t__ script_cmd_args_len ; 
 int /*<<< orphan*/  script_ptr ; 

void Script_TextMenu_b()
{
  script_ptr += 1 + script_cmd_args_len;
  UIShowMenu((script_cmd_args[0] * 256) + script_cmd_args[1], (script_cmd_args[2] * 256) + script_cmd_args[3], script_cmd_args[4], script_cmd_args[5]);
  script_action_complete = FALSE;
}