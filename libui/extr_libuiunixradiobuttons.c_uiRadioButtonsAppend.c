#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_4__* buttons; int /*<<< orphan*/  container; } ;
typedef  TYPE_1__ uiRadioButtons ;
struct TYPE_7__ {scalar_t__ len; } ;
typedef  int /*<<< orphan*/  GtkWidget ;
typedef  int /*<<< orphan*/  GtkRadioButton ;

/* Variables and functions */
 int /*<<< orphan*/ * GTK_RADIO_BUTTON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  G_CALLBACK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_ptr_array_add (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_ptr_array_index (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_signal_connect (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  gtk_container_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gtk_radio_button_new_with_label_from_widget (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  gtk_widget_show (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  onToggled ; 

void uiRadioButtonsAppend(uiRadioButtons *r, const char *text)
{
	GtkWidget *rb;
	GtkRadioButton *previous;

	previous = NULL;
	if (r->buttons->len > 0)
		previous = GTK_RADIO_BUTTON(g_ptr_array_index(r->buttons, 0));
	rb = gtk_radio_button_new_with_label_from_widget(previous, text);
	g_signal_connect(rb, "toggled", G_CALLBACK(onToggled), r);
	gtk_container_add(r->container, rb);
	g_ptr_array_add(r->buttons, rb);
	gtk_widget_show(rb);
}