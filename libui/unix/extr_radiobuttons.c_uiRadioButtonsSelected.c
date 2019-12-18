#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_3__* buttons; } ;
typedef  TYPE_1__ uiRadioButtons ;
typedef  scalar_t__ guint ;
struct TYPE_5__ {scalar_t__ len; } ;
typedef  int /*<<< orphan*/  GtkToggleButton ;

/* Variables and functions */
 int /*<<< orphan*/ * GTK_TOGGLE_BUTTON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_ptr_array_index (TYPE_3__*,scalar_t__) ; 
 scalar_t__ gtk_toggle_button_get_active (int /*<<< orphan*/ *) ; 

int uiRadioButtonsSelected(uiRadioButtons *r)
{
	GtkToggleButton *tb;
	guint i;

	for (i = 0; i < r->buttons->len; i++) {
		tb = GTK_TOGGLE_BUTTON(g_ptr_array_index(r->buttons, i));
		if (gtk_toggle_button_get_active(tb))
			return i;
	}
	return -1;
}