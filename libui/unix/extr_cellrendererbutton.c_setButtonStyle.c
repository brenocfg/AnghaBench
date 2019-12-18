#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  GtkWidgetPath ;
typedef  int /*<<< orphan*/  GtkWidget ;
typedef  int /*<<< orphan*/  GtkStyleContext ;

/* Variables and functions */
 int /*<<< orphan*/  GTK_STYLE_CLASS_BUTTON ; 
 int /*<<< orphan*/  GTK_TYPE_BUTTON ; 
 int /*<<< orphan*/  G_TYPE_NONE ; 
 int /*<<< orphan*/  gtk_style_context_add_class (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_style_context_get_path (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_style_context_get_state (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gtk_style_context_new () ; 
 int /*<<< orphan*/  gtk_style_context_set_parent (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_style_context_set_path (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_style_context_set_state (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gtk_widget_get_style_context (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_widget_path_append_type (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gtk_widget_path_copy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_widget_path_iter_set_object_type (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_widget_path_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiprivFUTURE_gtk_widget_path_iter_set_object_name (int /*<<< orphan*/ *,int,char*) ; 

__attribute__((used)) static GtkStyleContext *setButtonStyle(GtkWidget *widget)
{
	GtkStyleContext *base, *context;
	GtkWidgetPath *path;

	base = gtk_widget_get_style_context(widget);
	context = gtk_style_context_new();

	path = gtk_widget_path_copy(gtk_style_context_get_path(base));
	gtk_widget_path_append_type(path, G_TYPE_NONE);
	if (!uiprivFUTURE_gtk_widget_path_iter_set_object_name(path, -1, "button"))
		// not on 3.20; try the type
		gtk_widget_path_iter_set_object_type(path, -1, GTK_TYPE_BUTTON);

	gtk_style_context_set_path(context, path);
	gtk_style_context_set_parent(context, base);
	// the gtk3-demo example (which says we need to do this) uses gtk_widget_path_iter_get_state(path, -1) but that's not available until 3.14
	// TODO make a future for that too
	gtk_style_context_set_state(context, gtk_style_context_get_state(base));
	gtk_widget_path_unref(path);

	// and if the above widget path screwery stil doesn't work, this will
	gtk_style_context_add_class(context, GTK_STYLE_CLASS_BUTTON);

	return context;
}