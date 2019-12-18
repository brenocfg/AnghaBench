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
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FadeOut () ; 
 int /*<<< orphan*/  FadeSetSpeed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  script_action_complete ; 
 int /*<<< orphan*/ * script_cmd_args ; 
 scalar_t__ script_cmd_args_len ; 
 int /*<<< orphan*/  script_ptr ; 

void Script_FadeOut_b()
{
  FadeOut();
  FadeSetSpeed(script_cmd_args[0]);
  script_ptr += 1 + script_cmd_args_len;
  script_action_complete = FALSE;
}