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
struct TYPE_2__ {scalar_t__ bank; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 TYPE_1__* input_script_ptrs ; 
 int /*<<< orphan*/  script_action_complete ; 
 int* script_cmd_args ; 
 scalar_t__ script_cmd_args_len ; 
 int /*<<< orphan*/  script_ptr ; 

void Script_RemoveInputScript_b()
{
  UBYTE input, index;

  input = script_cmd_args[0];

  index = 0;
  for (index = 0; index != 8; ++index)
  {
    if (input & 1)
    {
      input_script_ptrs[index].bank = 0;
    }
    input = input >> 1;
  }

  script_action_complete = TRUE;
  script_ptr += 1 + script_cmd_args_len;
}