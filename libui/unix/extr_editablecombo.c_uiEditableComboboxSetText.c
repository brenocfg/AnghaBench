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
struct TYPE_3__ {int /*<<< orphan*/  onChangedSignal; int /*<<< orphan*/  combobox; int /*<<< orphan*/  bin; } ;
typedef  TYPE_1__ uiEditableCombobox ;
typedef  int /*<<< orphan*/  GtkEntry ;

/* Variables and functions */
 int /*<<< orphan*/ * GTK_ENTRY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_signal_handler_block (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_signal_handler_unblock (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_bin_get_child (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_entry_set_text (int /*<<< orphan*/ *,char const*) ; 

void uiEditableComboboxSetText(uiEditableCombobox *c, const char *text)
{
	GtkEntry *e;

	// we need to inhibit sending of ::changed because this WILL send a ::changed otherwise
	g_signal_handler_block(c->combobox, c->onChangedSignal);
	// since there isn't a gtk_combo_box_text_set_active_text()...
	e = GTK_ENTRY(gtk_bin_get_child(c->bin));
	gtk_entry_set_text(e, text);
	g_signal_handler_unblock(c->combobox, c->onChangedSignal);
}