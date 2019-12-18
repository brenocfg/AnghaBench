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
typedef  size_t UWORD ;
typedef  int UBYTE ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int rand () ; 
 int* script_cmd_args ; 
 scalar_t__ script_cmd_args_len ; 
 int /*<<< orphan*/  script_continue ; 
 int /*<<< orphan*/  script_ptr ; 
 int* script_variables ; 

void Script_SetFlagRandomValue_b()
{
  UBYTE rand_val;
  UBYTE modulo;
  UBYTE offset;
  UWORD ptr = (script_cmd_args[0] * 256) + script_cmd_args[1];
  rand_val = rand();
  offset = script_cmd_args[2];
  modulo = script_cmd_args[3] + 1;
  script_variables[ptr] = offset + (rand_val % modulo);
  script_ptr += 1 + script_cmd_args_len;
  script_continue = TRUE;
}