#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  toggledSignal; } ;
typedef  TYPE_1__ uiprivDateTimePickerWidget ;
typedef  int /*<<< orphan*/  gboolean ;

/* Variables and functions */
 int /*<<< orphan*/  GTK_TOGGLE_BUTTON (TYPE_1__*) ; 
 int /*<<< orphan*/  g_signal_handler_block (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_signal_handler_unblock (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_toggle_button_set_active (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void setActive(uiprivDateTimePickerWidget *d, gboolean active)
{
	g_signal_handler_block(d, d->toggledSignal);
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(d), active);
	g_signal_handler_unblock(d, d->toggledSignal);
}