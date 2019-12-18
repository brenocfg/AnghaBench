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
 int FALSE ; 
#define  OPERATOR_EQ 133 
#define  OPERATOR_GT 132 
#define  OPERATOR_GTE 131 
#define  OPERATOR_LT 130 
#define  OPERATOR_LTE 129 
#define  OPERATOR_NE 128 
 int /*<<< orphan*/  TRUE ; 
 int* script_cmd_args ; 
 scalar_t__ script_cmd_args_len ; 
 int /*<<< orphan*/  script_continue ; 
 scalar_t__ script_ptr ; 
 size_t script_ptr_x ; 
 size_t script_ptr_y ; 
 scalar_t__ script_start_ptr ; 
 int* script_variables ; 

void Script_IfValueCompare_b()
{
  UBYTE match;
  UBYTE a = script_variables[script_ptr_x];
  UBYTE b = script_variables[script_ptr_y];

  switch (script_cmd_args[0])
  {
  case OPERATOR_EQ:
    match = a == b;
    break;
  case OPERATOR_LT:
    match = a < b;
    break;
  case OPERATOR_LTE:
    match = a <= b;
    break;
  case OPERATOR_GT:
    match = a > b;
    break;
  case OPERATOR_GTE:
    match = a >= b;
    break;
  case OPERATOR_NE:
    match = a != b;
    break;
  default:
    match = FALSE;
  }

  if (match)
  { // True path, jump to position specified by ptr
    script_ptr = script_start_ptr + (script_cmd_args[1] * 256) + script_cmd_args[2];
  }
  else
  { // False path, skip to next command
    script_ptr += 1 + script_cmd_args_len;
  }
  script_continue = TRUE;
}