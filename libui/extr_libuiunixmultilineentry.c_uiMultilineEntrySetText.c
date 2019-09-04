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
struct TYPE_3__ {int /*<<< orphan*/  onChangedSignal; int /*<<< orphan*/  textbuf; } ;
typedef  TYPE_1__ uiMultilineEntry ;

/* Variables and functions */
 int /*<<< orphan*/  g_signal_handler_block (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_signal_handler_unblock (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_text_buffer_set_text (int /*<<< orphan*/ ,char const*,int) ; 

void uiMultilineEntrySetText(uiMultilineEntry *e, const char *text)
{
	// we need to inhibit sending of ::changed because this WILL send a ::changed otherwise
	g_signal_handler_block(e->textbuf, e->onChangedSignal);
	gtk_text_buffer_set_text(e->textbuf, text, -1);
	g_signal_handler_unblock(e->textbuf, e->onChangedSignal);
}