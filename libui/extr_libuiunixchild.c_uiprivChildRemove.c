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
struct TYPE_4__ {int /*<<< orphan*/ * box; int /*<<< orphan*/  oldvalign; int /*<<< orphan*/  widget; int /*<<< orphan*/  oldvexpand; int /*<<< orphan*/  oldhalign; int /*<<< orphan*/  oldhexpand; int /*<<< orphan*/  parent; int /*<<< orphan*/  c; } ;
typedef  TYPE_1__ uiprivChild ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  gtk_widget_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_widget_set_halign (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_widget_set_hexpand (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_widget_set_valign (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_widget_set_vexpand (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiControlSetParent (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiUnixControl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiUnixControlSetContainer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiprivFree (TYPE_1__*) ; 

void uiprivChildRemove(uiprivChild *c)
{
	uiControlSetParent(c->c, NULL);
	uiUnixControlSetContainer(uiUnixControl(c->c), c->parent, TRUE);

	gtk_widget_set_hexpand(c->widget, c->oldhexpand);
	gtk_widget_set_halign(c->widget, c->oldhalign);
	gtk_widget_set_vexpand(c->widget, c->oldvexpand);
	gtk_widget_set_valign(c->widget, c->oldvalign);

	if (c->box != NULL)
		gtk_widget_destroy(c->box);

	uiprivFree(c);
}