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
typedef  int uiTableNotification ;
typedef  int /*<<< orphan*/  uiTableModel ;
typedef  int /*<<< orphan*/  intmax_t ;
typedef  int /*<<< orphan*/  GtkTreePath ;
typedef  int /*<<< orphan*/  GtkTreeModel ;
typedef  int /*<<< orphan*/  GtkTreeIter ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/ * GTK_TREE_MODEL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  complain (char*,...) ; 
 int /*<<< orphan*/  gtk_tree_model_get_iter (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_tree_model_row_changed (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_tree_model_row_deleted (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_tree_model_row_inserted (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_tree_path_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gtk_tree_path_new_from_indices (int /*<<< orphan*/ ,int) ; 
#define  uiTableCellChanged 130 
#define  uiTableRowDeleted 129 
#define  uiTableRowInserted 128 

void uiTableModelNotify(uiTableModel *m, uiTableNotification notification, intmax_t row, intmax_t column)
{
	GtkTreeModel *model = GTK_TREE_MODEL(m);
	GtkTreePath *path;
	GtkTreeIter iter;

	path = gtk_tree_path_new_from_indices(row, -1);
	switch (notification) {
	case uiTableRowInserted:
		if (gtk_tree_model_get_iter(model, &iter, path) == FALSE)
			complain("invalid row given to row inserted in uiTableModelNotify()");
		gtk_tree_model_row_inserted(model, path, &iter);
		break;
	case uiTableRowDeleted:
		gtk_tree_model_row_deleted(model, path);
		break;
	case uiTableCellChanged:
		if (gtk_tree_model_get_iter(model, &iter, path) == FALSE)
			complain("invalid row given to row changed in uiTableModelNotify()");
		gtk_tree_model_row_changed(model, path, &iter);
		break;
	default:
		complain("unknown uiTable notification %d in uiTableModelNotify()", notification);
	}
	gtk_tree_path_free(path);
}