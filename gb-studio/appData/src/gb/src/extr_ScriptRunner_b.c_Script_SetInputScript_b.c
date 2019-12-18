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
typedef  int UBYTE ;
struct TYPE_2__ {int bank; int offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 TYPE_1__* input_script_ptrs ; 
 int /*<<< orphan*/  script_action_complete ; 
 int* script_cmd_args ; 
 scalar_t__ script_cmd_args_len ; 
 int /*<<< orphan*/  script_ptr ; 

void Script_SetInputScript_b()
{
  UBYTE input, index;

  input = script_cmd_args[0];

  index = 0;
  while (!(input & 1) && input != 0)
  {
    index += 1;
    input = input >> 1;
  }

  input_script_ptrs[index].bank = script_cmd_args[1];
  input_script_ptrs[index].offset = (script_cmd_args[2] * 256) + script_cmd_args[3];

  script_action_complete = TRUE;
  script_ptr += 1 + script_cmd_args_len;
}