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
typedef  int /*<<< orphan*/  UWORD ;

/* Variables and functions */
 int MENU_CANCEL_ON_B_PRESSED ; 
 int MENU_CANCEL_ON_LAST_OPTION ; 
 int /*<<< orphan*/  UIShowMenu (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void UIShowChoice(UWORD flag_index, UWORD line)
{
  UIShowMenu(flag_index, line, 0, MENU_CANCEL_ON_B_PRESSED | MENU_CANCEL_ON_LAST_OPTION);
}