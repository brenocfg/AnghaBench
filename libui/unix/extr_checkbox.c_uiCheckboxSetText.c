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
struct TYPE_3__ {int /*<<< orphan*/  button; } ;
typedef  TYPE_1__ uiCheckbox ;

/* Variables and functions */
 int /*<<< orphan*/  GTK_BUTTON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_button_set_label (int /*<<< orphan*/ ,char const*) ; 

void uiCheckboxSetText(uiCheckbox *c, const char *text)
{
	gtk_button_set_label(GTK_BUTTON(c->button), text);
}