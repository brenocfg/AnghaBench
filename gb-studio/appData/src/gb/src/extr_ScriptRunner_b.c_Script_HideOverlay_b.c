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
 int /*<<< orphan*/  MENU_CLOSED_Y ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  UISetPos (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ script_cmd_args_len ; 
 int /*<<< orphan*/  script_continue ; 
 int /*<<< orphan*/  script_ptr ; 

void Script_HideOverlay_b()
{
  UISetPos(0, MENU_CLOSED_Y);
  script_ptr += 1 + script_cmd_args_len;
  script_continue = TRUE;
}