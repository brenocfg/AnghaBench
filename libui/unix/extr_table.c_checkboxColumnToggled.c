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
typedef  int /*<<< orphan*/  uiTableValue ;
struct checkboxColumnParams {int /*<<< orphan*/  m; int /*<<< orphan*/  modelColumn; } ;
typedef  scalar_t__ gpointer ;
typedef  int /*<<< orphan*/  gchar ;
typedef  int /*<<< orphan*/  GtkTreePath ;
typedef  int /*<<< orphan*/  GtkTreeIter ;
typedef  int /*<<< orphan*/  GtkCellRendererToggle ;
typedef  int /*<<< orphan*/  GValue ;

/* Variables and functions */
 int /*<<< orphan*/  GTK_CELL_RENDERER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_TREE_MODEL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  G_VALUE_INIT ; 
 int /*<<< orphan*/  checkboxColumnDataFunc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int g_value_get_int (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_value_unset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_tree_model_get_iter (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_tree_model_get_value (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_tree_path_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gtk_tree_path_new_from_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  onEdited (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiFreeTableValue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * uiNewTableValueInt (int) ; 

__attribute__((used)) static void checkboxColumnToggled(GtkCellRendererToggle *r, gchar *pathstr, gpointer data)
{
	struct checkboxColumnParams *p = (struct checkboxColumnParams *) data;
	GValue value = G_VALUE_INIT;
	int v;
	uiTableValue *tvalue;
	GtkTreePath *path;
	GtkTreeIter iter;

	path = gtk_tree_path_new_from_string(pathstr);
	gtk_tree_model_get_iter(GTK_TREE_MODEL(p->m), &iter, path);
	gtk_tree_path_free(path);
	gtk_tree_model_get_value(GTK_TREE_MODEL(p->m), &iter, p->modelColumn, &value);
	v = g_value_get_int(&value);
	g_value_unset(&value);
	tvalue = uiNewTableValueInt(!v);
	onEdited(p->m, p->modelColumn, pathstr, tvalue, NULL);
	uiFreeTableValue(tvalue);
	// and update the column TODO copy comment here
	// TODO avoid fetching the model data twice
	checkboxColumnDataFunc(NULL, GTK_CELL_RENDERER(r), GTK_TREE_MODEL(p->m), &iter, data);
}