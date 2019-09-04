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
typedef  int /*<<< orphan*/  GtkTreePath ;

/* Variables and functions */
 int /*<<< orphan*/  GTK_TREE_MODEL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_tree_model_row_deleted (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_tree_path_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gtk_tree_path_new_from_indices (int,int) ; 

void uiTableModelRowDeleted(uiTableModel *m, int oldIndex)
{
	GtkTreePath *path;

	path = gtk_tree_path_new_from_indices(oldIndex, -1);
	gtk_tree_model_row_deleted(GTK_TREE_MODEL(m), path);
	gtk_tree_path_free(path);
}