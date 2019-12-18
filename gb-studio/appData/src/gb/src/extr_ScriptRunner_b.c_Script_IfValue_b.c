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
 scalar_t__ script_start_ptr ; 
 int* script_variables ; 

void Script_IfValue_b()
{
  UBYTE value, match;
  UWORD ptr = (script_cmd_args[0] * 256) + script_cmd_args[1];
  value = script_variables[ptr];

  switch (script_cmd_args[2])
  {
  case OPERATOR_EQ:
    match = value == script_cmd_args[3];
    break;
  case OPERATOR_LT:
    match = value < script_cmd_args[3];
    break;
  case OPERATOR_LTE:
    match = value <= script_cmd_args[3];
    break;
  case OPERATOR_GT:
    match = value > script_cmd_args[3];
    break;
  case OPERATOR_GTE:
    match = value >= script_cmd_args[3];
    break;
  case OPERATOR_NE:
    match = value != script_cmd_args[3];
    break;
  default:
    match = FALSE;
  }

  if (match)
  { // True path, jump to position specified by ptr
    script_ptr = script_start_ptr + (script_cmd_args[4] * 256) + script_cmd_args[5];
  }
  else
  { // False path, skip to next command
    script_ptr += 1 + script_cmd_args_len;
  }
  script_continue = TRUE;
}