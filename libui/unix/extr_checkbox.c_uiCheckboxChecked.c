#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  toggleButton; } ;
typedef  TYPE_1__ uiCheckbox ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ gtk_toggle_button_get_active (int /*<<< orphan*/ ) ; 

int uiCheckboxChecked(uiCheckbox *c)
{
	return gtk_toggle_button_get_active(c->toggleButton) != FALSE;
}