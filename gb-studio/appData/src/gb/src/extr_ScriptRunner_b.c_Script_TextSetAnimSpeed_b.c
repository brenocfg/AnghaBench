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
 int /*<<< orphan*/  TRUE ; 
 void** script_cmd_args ; 
 scalar_t__ script_cmd_args_len ; 
 int /*<<< orphan*/  script_continue ; 
 int /*<<< orphan*/  script_ptr ; 
 void* text_draw_speed ; 
 void* text_in_speed ; 
 void* text_out_speed ; 

void Script_TextSetAnimSpeed_b()
{
  text_in_speed = script_cmd_args[0];
  text_out_speed = script_cmd_args[1];
  text_draw_speed = script_cmd_args[2];
  script_ptr += 1 + script_cmd_args_len;
  script_continue = TRUE;
}