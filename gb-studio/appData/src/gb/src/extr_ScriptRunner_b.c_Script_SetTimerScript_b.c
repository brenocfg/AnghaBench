#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int bank; int offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  script_action_complete ; 
 int* script_cmd_args ; 
 scalar_t__ script_cmd_args_len ; 
 int /*<<< orphan*/  script_ptr ; 
 int timer_script_duration ; 
 TYPE_1__ timer_script_ptr ; 
 int timer_script_time ; 

void Script_SetTimerScript_b()
{
  timer_script_duration = script_cmd_args[0];
  timer_script_time = script_cmd_args[0];
  timer_script_ptr.bank = script_cmd_args[1];
  timer_script_ptr.offset = (script_cmd_args[2] * 256) + script_cmd_args[3];

  script_action_complete = TRUE;
  script_ptr += 1 + script_cmd_args_len;
}