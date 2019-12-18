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
typedef  int /*<<< orphan*/  uiTableModel ;
typedef  int /*<<< orphan*/  GtkTreePath ;
typedef  int /*<<< orphan*/  GtkTreeIter ;

/* Variables and functions */
 int /*<<< orphan*/  GTK_TREE_MODEL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_tree_model_get_iter (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_tree_path_free (int /*<<< orphan*/ *) ; 
 int* gtk_tree_path_get_indices (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gtk_tree_path_new_from_string (char const*) ; 
 int /*<<< orphan*/  uiprivTableModelSetCellValue (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void onEdited(uiTableModel *m, int column, const char *pathstr, const uiTableValue *tvalue, GtkTreeIter *iter)
{
	GtkTreePath *path;
	int row;

	path = gtk_tree_path_new_from_string(pathstr);
	row = gtk_tree_path_get_indices(path)[0];
	if (iter != NULL)
		gtk_tree_model_get_iter(GTK_TREE_MODEL(m), iter, path);
	gtk_tree_path_free(path);
	uiprivTableModelSetCellValue(m, row, column, tvalue);
}