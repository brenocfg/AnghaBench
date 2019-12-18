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
 int* script_cmd_args ; 
 scalar_t__ script_cmd_args_len ; 
 int /*<<< orphan*/  script_continue ; 
 int /*<<< orphan*/  script_ptr ; 
 int* script_variables ; 

void Script_VariableClearFlags_b()
{
  UWORD ptr = (script_cmd_args[0] * 256) + script_cmd_args[1];
  UBYTE a = script_variables[ptr];
  UBYTE b = script_cmd_args[2];
  script_variables[ptr] = a & ~b;
  script_ptr += 1 + script_cmd_args_len;
  script_continue = TRUE;
}