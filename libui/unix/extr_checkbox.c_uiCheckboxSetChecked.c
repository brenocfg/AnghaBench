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
struct TYPE_3__ {int /*<<< orphan*/  onToggledSignal; int /*<<< orphan*/  toggleButton; } ;
typedef  TYPE_1__ uiCheckbox ;
typedef  int /*<<< orphan*/  gboolean ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  g_signal_handler_block (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_signal_handler_unblock (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_toggle_button_set_active (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void uiCheckboxSetChecked(uiCheckbox *c, int checked)
{
	gboolean active;

	active = FALSE;
	if (checked)
		active = TRUE;
	// we need to inhibit sending of ::toggled because this WILL send a ::toggled otherwise
	g_signal_handler_block(c->toggleButton, c->onToggledSignal);
	gtk_toggle_button_set_active(c->toggleButton, active);
	g_signal_handler_unblock(c->toggleButton, c->onToggledSignal);
}