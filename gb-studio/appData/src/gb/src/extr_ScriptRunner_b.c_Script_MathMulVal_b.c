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
 scalar_t__ script_cmd_args_len ; 
 int /*<<< orphan*/  script_continue ; 
 int /*<<< orphan*/  script_ptr ; 
 size_t script_ptr_x ; 
 size_t script_ptr_y ; 
 int* script_variables ; 

void Script_MathMulVal_b()
{
  UBYTE a = script_variables[script_ptr_x];
  UBYTE b = script_variables[script_ptr_y];
  script_variables[script_ptr_x] = a * b;
  script_ptr += 1 + script_cmd_args_len;
  script_continue = TRUE;
}