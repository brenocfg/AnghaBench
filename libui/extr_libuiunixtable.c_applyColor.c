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
typedef  int /*<<< orphan*/  GtkTreeModel ;
typedef  int /*<<< orphan*/  GtkTreeIter ;
typedef  int /*<<< orphan*/  GtkCellRenderer ;
typedef  int /*<<< orphan*/  GdkRGBA ;
typedef  int /*<<< orphan*/  GValue ;

/* Variables and functions */
 int /*<<< orphan*/ * FALSE ; 
 int /*<<< orphan*/  G_VALUE_INIT ; 
 int /*<<< orphan*/  g_object_set (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ g_value_get_boxed (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_value_unset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_tree_model_get_value (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void applyColor(GtkTreeModel *m, GtkTreeIter *iter, int modelColumn, GtkCellRenderer *r, const char *prop, const char *propSet)
{
	GValue value = G_VALUE_INIT;
	GdkRGBA *rgba;

	gtk_tree_model_get_value(m, iter, modelColumn, &value);
	rgba = (GdkRGBA *) g_value_get_boxed(&value);
	if (rgba != NULL)
		g_object_set(r, prop, rgba, NULL);
	else
		g_object_set(r, propSet, FALSE, NULL);
	g_value_unset(&value);
}