#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {void* changing; int /*<<< orphan*/  buttons; } ;
typedef  TYPE_1__ uiRadioButtons ;
typedef  void* gboolean ;
typedef  int /*<<< orphan*/  GtkToggleButton ;

/* Variables and functions */
 void* FALSE ; 
 int /*<<< orphan*/ * GTK_TOGGLE_BUTTON (int /*<<< orphan*/ ) ; 
 void* TRUE ; 
 int /*<<< orphan*/  g_ptr_array_index (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gtk_toggle_button_set_active (int /*<<< orphan*/ *,void*) ; 
 int uiRadioButtonsSelected (TYPE_1__*) ; 

void uiRadioButtonsSetSelected(uiRadioButtons *r, int n)
{
	GtkToggleButton *tb;
	gboolean active;

	active = TRUE;
	// TODO this doesn't work
	if (n == -1) {
		n = uiRadioButtonsSelected(r);
		if (n == -1)		// no selection; keep it that way
			return;
		active = FALSE;
	}
	tb = GTK_TOGGLE_BUTTON(g_ptr_array_index(r->buttons, n));
	// this is easier than remembering all the signals
	r->changing = TRUE;
	gtk_toggle_button_set_active(tb, active);
	r->changing = FALSE;
}