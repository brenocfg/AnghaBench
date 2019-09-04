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
typedef  int /*<<< orphan*/  gpointer ;
typedef  int /*<<< orphan*/  gboolean ;
typedef  int /*<<< orphan*/  GtkTreePath ;
typedef  int /*<<< orphan*/  GtkTreeIter ;

/* Variables and functions */
 int /*<<< orphan*/  GTK_TREE_MODEL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  gtk_tree_model_get_iter (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_tree_model_row_changed (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_tree_path_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gtk_tree_path_new_from_indices (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  model ; 

__attribute__((used)) static gboolean pulseTable(gpointer data)
{
	GtkTreePath *path;
	GtkTreeIter iter;

	path = gtk_tree_path_new_from_indices(0, -1);
	gtk_tree_model_get_iter(GTK_TREE_MODEL(model), &iter, path);
	gtk_tree_model_row_changed(GTK_TREE_MODEL(model), path, &iter);
	gtk_tree_path_free(path);
	return TRUE;
}