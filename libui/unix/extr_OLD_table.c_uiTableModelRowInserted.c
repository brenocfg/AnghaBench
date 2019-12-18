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
typedef  int /*<<< orphan*/  uiTableModel ;
struct TYPE_3__ {int /*<<< orphan*/  user_data; int /*<<< orphan*/  stamp; } ;
typedef  int /*<<< orphan*/  GtkTreePath ;
typedef  TYPE_1__ GtkTreeIter ;

/* Variables and functions */
 int /*<<< orphan*/  GINT_TO_POINTER (int) ; 
 int /*<<< orphan*/  GTK_TREE_MODEL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAMP_GOOD ; 
 int /*<<< orphan*/  gtk_tree_model_row_inserted (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  gtk_tree_path_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gtk_tree_path_new_from_indices (int,int) ; 

void uiTableModelRowInserted(uiTableModel *m, int newIndex)
{
	GtkTreePath *path;
	GtkTreeIter iter;

	path = gtk_tree_path_new_from_indices(newIndex, -1);
	iter.stamp = STAMP_GOOD;
	iter.user_data = GINT_TO_POINTER(newIndex);
	gtk_tree_model_row_inserted(GTK_TREE_MODEL(m), path, &iter);
	gtk_tree_path_free(path);
}