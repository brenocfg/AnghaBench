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
typedef  int UBYTE ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int* script_cmd_args ; 
 scalar_t__ script_cmd_args_len ; 
 int /*<<< orphan*/  script_continue ; 
 int /*<<< orphan*/  script_ptr ; 
 scalar_t__ text_in_speed ; 
 scalar_t__ text_out_speed ; 
 scalar_t__ tmp_text_in_speed ; 
 scalar_t__ tmp_text_out_speed ; 

void Script_TextMulti_b()
{
  UBYTE mode;
  mode = script_cmd_args[0];

  if (mode == 0)
  {
    tmp_text_out_speed = text_out_speed;
    text_out_speed = 0;
  }
  else if (mode == 1)
  {
    tmp_text_in_speed = text_in_speed;
    text_in_speed = 0;
  }
  else if (mode == 2)
  {
    text_out_speed = tmp_text_out_speed;
  }
  else if (mode == 3)
  {
    text_in_speed = tmp_text_in_speed;
    text_out_speed = tmp_text_out_speed;
  }

  script_ptr += 1 + script_cmd_args_len;
  script_continue = TRUE;
}