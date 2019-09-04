#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * box; int /*<<< orphan*/  widget; } ;
typedef  TYPE_1__ uiprivChild ;
typedef  int /*<<< orphan*/  uiControl ;
typedef  int /*<<< orphan*/  GtkWidget ;
typedef  int /*<<< orphan*/  GtkContainer ;

/* Variables and functions */
 int /*<<< orphan*/  GTK_ALIGN_FILL ; 
 int /*<<< orphan*/  GTK_CONTAINER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_ORIENTATION_HORIZONTAL ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * gtk_box_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_container_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_widget_set_halign (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_widget_set_hexpand (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_widget_set_valign (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_widget_set_vexpand (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_widget_show (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiprivChildSetMargined (TYPE_1__*,int) ; 
 TYPE_1__* uiprivNewChild (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

uiprivChild *uiprivNewChildWithBox(uiControl *child, uiControl *parent, GtkContainer *parentContainer, int margined)
{
	uiprivChild *c;
	GtkWidget *box;

	if (child == NULL)
		return NULL;
	box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	gtk_widget_show(box);
	c = uiprivNewChild(child, parent, GTK_CONTAINER(box));
	gtk_widget_set_hexpand(c->widget, TRUE);
	gtk_widget_set_halign(c->widget, GTK_ALIGN_FILL);
	gtk_widget_set_vexpand(c->widget, TRUE);
	gtk_widget_set_valign(c->widget, GTK_ALIGN_FILL);
	c->box = box;
	gtk_container_add(parentContainer, c->box);
	uiprivChildSetMargined(c, margined);
	return c;
}