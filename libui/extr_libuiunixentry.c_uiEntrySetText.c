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
struct TYPE_3__ {int /*<<< orphan*/  onChangedSignal; int /*<<< orphan*/  editable; int /*<<< orphan*/  entry; } ;
typedef  TYPE_1__ uiEntry ;

/* Variables and functions */
 int /*<<< orphan*/  g_signal_handler_block (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_signal_handler_unblock (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_entry_set_text (int /*<<< orphan*/ ,char const*) ; 

void uiEntrySetText(uiEntry *e, const char *text)
{
	// we need to inhibit sending of ::changed because this WILL send a ::changed otherwise
	g_signal_handler_block(e->editable, e->onChangedSignal);
	gtk_entry_set_text(e->entry, text);
	g_signal_handler_unblock(e->editable, e->onChangedSignal);
	// don't queue the control for resize; entry sizes are independent of their contents
}