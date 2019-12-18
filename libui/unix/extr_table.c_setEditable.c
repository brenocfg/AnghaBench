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
typedef  int /*<<< orphan*/  uiTableModel ;
typedef  int gboolean ;
typedef  int /*<<< orphan*/  GtkTreePath ;
typedef  int /*<<< orphan*/  GtkTreeIter ;
typedef  int /*<<< orphan*/  GtkCellRenderer ;

/* Variables and functions */
 int /*<<< orphan*/  GTK_TREE_MODEL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_object_set (int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gtk_tree_model_get_path (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int* gtk_tree_path_get_indices (int /*<<< orphan*/ *) ; 
 scalar_t__ uiprivTableModelCellEditable (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void setEditable(uiTableModel *m, GtkTreeIter *iter, int modelColumn, GtkCellRenderer *r, const char *prop)
{
	GtkTreePath *path;
	int row;
	gboolean editable;

	// TODO avoid the need for this
	path = gtk_tree_model_get_path(GTK_TREE_MODEL(m), iter);
	row = gtk_tree_path_get_indices(path)[0];
	editable = uiprivTableModelCellEditable(m, row, modelColumn) != 0;
	g_object_set(r, prop, editable, NULL);
}