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
typedef  int /*<<< orphan*/  GtkTreeViewColumn ;
typedef  int /*<<< orphan*/  GtkTreeIter ;
typedef  int /*<<< orphan*/  GtkCellRenderer ;

/* Variables and functions */
 int /*<<< orphan*/  GTK_ALIGN_CENTER ; 
 int /*<<< orphan*/  GTK_CONTAINER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GTK_ORIENTATION_HORIZONTAL ; 
 int /*<<< orphan*/  GTK_ORIENTATION_VERTICAL ; 
 int /*<<< orphan*/  GTK_SCROLLED_WINDOW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GTK_SHADOW_IN ; 
 int /*<<< orphan*/  GTK_TREE_MODEL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GTK_TREE_VIEW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GTK_WINDOW_TOPLEVEL ; 
 int /*<<< orphan*/  G_CALLBACK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  G_TYPE_INT ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  g_signal_connect (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_box_new (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gtk_button_new_with_label (char*) ; 
 int /*<<< orphan*/ * gtk_cell_renderer_progress_new () ; 
 int /*<<< orphan*/  gtk_container_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_container_set_border_width (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gtk_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_list_store_append (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_list_store_new (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_list_store_set (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gtk_main () ; 
 int /*<<< orphan*/  gtk_progress_bar_new () ; 
 int /*<<< orphan*/  gtk_scrolled_window_new (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_scrolled_window_set_shadow_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_tree_view_append_column (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gtk_tree_view_column_new () ; 
 int /*<<< orphan*/  gtk_tree_view_column_pack_start (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_tree_view_column_set_cell_data_func (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_tree_view_column_set_resizable (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_tree_view_column_set_title (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  gtk_tree_view_new_with_model (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_widget_set_halign (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_widget_set_vexpand (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_widget_show_all (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_window_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hbox ; 
 int /*<<< orphan*/  hbox2 ; 
 int /*<<< orphan*/  mainwin ; 
 int /*<<< orphan*/  model ; 
 int /*<<< orphan*/  onClosing ; 
 int /*<<< orphan*/  onStartProgressClicked ; 
 int /*<<< orphan*/  onStartTableClicked ; 
 int /*<<< orphan*/  pbarDataFunc ; 
 int /*<<< orphan*/  progressbar ; 
 int /*<<< orphan*/  scrolledWindow ; 
 int /*<<< orphan*/  startProgress ; 
 int /*<<< orphan*/  startTable ; 
 int /*<<< orphan*/  treeview ; 
 int /*<<< orphan*/  vbox ; 

int main(void)
{
	GtkTreeIter iter;
	GtkTreeViewColumn *col;
	GtkCellRenderer *r;

	gtk_init(NULL, NULL);

	mainwin = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect(mainwin, "delete-event", G_CALLBACK(onClosing), NULL);

	vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 12);
	gtk_container_set_border_width(GTK_CONTAINER(vbox), 12);
	gtk_container_add(GTK_CONTAINER(mainwin), vbox);

	hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 6);
	gtk_widget_set_halign(hbox, GTK_ALIGN_CENTER);
	gtk_container_add(GTK_CONTAINER(vbox), hbox);

	startProgress = gtk_button_new_with_label("Start Progress Bar");
	g_signal_connect(startProgress, "clicked", G_CALLBACK(onStartProgressClicked), NULL);
	gtk_container_add(GTK_CONTAINER(hbox), startProgress);

	startTable = gtk_button_new_with_label("Start Table Cell Renderer");
	g_signal_connect(startTable, "clicked", G_CALLBACK(onStartTableClicked), NULL);
	gtk_container_add(GTK_CONTAINER(hbox), startTable);

	progressbar = gtk_progress_bar_new();
	gtk_container_add(GTK_CONTAINER(vbox), progressbar);

	scrolledWindow = gtk_scrolled_window_new(NULL, NULL);
	gtk_scrolled_window_set_shadow_type(GTK_SCROLLED_WINDOW(scrolledWindow), GTK_SHADOW_IN);
	gtk_widget_set_vexpand(scrolledWindow, TRUE);
	gtk_container_add(GTK_CONTAINER(vbox), scrolledWindow);

	model = gtk_list_store_new(1, G_TYPE_INT);
	gtk_list_store_append(model, &iter);
	gtk_list_store_set(model, &iter,
		0, 0,
		-1);

	treeview = gtk_tree_view_new_with_model(GTK_TREE_MODEL(model));
	gtk_container_add(GTK_CONTAINER(scrolledWindow), treeview);

	col = gtk_tree_view_column_new();
	gtk_tree_view_column_set_resizable(col, TRUE);
	gtk_tree_view_column_set_title(col, "Column");
	gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), col);

	r = gtk_cell_renderer_progress_new();
	gtk_tree_view_column_pack_start(col, r, TRUE);
	gtk_tree_view_column_set_cell_data_func(col, r, pbarDataFunc, NULL, NULL);

	hbox2 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 6);
	gtk_widget_set_halign(hbox2, GTK_ALIGN_CENTER);
	gtk_container_add(GTK_CONTAINER(vbox), hbox2);

	gtk_container_add(GTK_CONTAINER(hbox2), gtk_button_new_with_label("These buttons"));
	gtk_container_add(GTK_CONTAINER(hbox2), gtk_button_new_with_label("do nothing"));
	gtk_container_add(GTK_CONTAINER(hbox2), gtk_button_new_with_label("when clicked"));

	gtk_widget_show_all(mainwin);
	gtk_main();
	return 0;
}