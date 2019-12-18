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
 int /*<<< orphan*/  script_continue ; 
 scalar_t__ script_ptr ; 
 scalar_t__ script_start_ptr ; 

void Script_Goto_b()
{
  script_ptr = script_start_ptr + (script_cmd_args[0] * 256) + script_cmd_args[1];
  script_continue = TRUE;
}