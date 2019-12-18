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
 int* script_cmd_args ; 
 scalar_t__ script_cmd_args_len ; 
 int /*<<< orphan*/  script_continue ; 
 scalar_t__ script_ptr ; 
 scalar_t__ script_start_ptr ; 
 scalar_t__* script_variables ; 

void Script_IfFlag_b()
{
  if (script_variables[(script_cmd_args[0] * 256) + script_cmd_args[1]])
  { // True path, jump to position specified by ptr
    script_ptr = script_start_ptr + (script_cmd_args[2] * 256) + script_cmd_args[3];
  }
  else
  { // False path, skip to next command
    script_ptr += 1 + script_cmd_args_len;
  }
  script_continue = TRUE;
}