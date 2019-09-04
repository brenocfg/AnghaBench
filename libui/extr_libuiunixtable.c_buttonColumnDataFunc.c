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
struct buttonColumnParams {int /*<<< orphan*/  t; int /*<<< orphan*/  clickableColumn; int /*<<< orphan*/  m; int /*<<< orphan*/  modelColumn; } ;
typedef  scalar_t__ gpointer ;
typedef  int /*<<< orphan*/  gchar ;
typedef  int /*<<< orphan*/  GtkTreeViewColumn ;
typedef  int /*<<< orphan*/  GtkTreeModel ;
typedef  int /*<<< orphan*/  GtkTreeIter ;
typedef  int /*<<< orphan*/  GtkCellRenderer ;
typedef  int /*<<< orphan*/  GValue ;

/* Variables and functions */
 int /*<<< orphan*/  G_VALUE_INIT ; 
 int /*<<< orphan*/  applyBackgroundColor (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_object_set (int /*<<< orphan*/ *,char*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_value_get_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_value_unset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_tree_model_get_value (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setEditable (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void buttonColumnDataFunc(GtkTreeViewColumn *c, GtkCellRenderer *r, GtkTreeModel *m, GtkTreeIter *iter, gpointer data)
{
	struct buttonColumnParams *p = (struct buttonColumnParams *) data;
	GValue value = G_VALUE_INIT;
	const gchar *str;

	gtk_tree_model_get_value(m, iter, p->modelColumn, &value);
	str = g_value_get_string(&value);
	g_object_set(r, "text", str, NULL);
	g_value_unset(&value);

	setEditable(p->m, iter, p->clickableColumn, r, "sensitive");

	applyBackgroundColor(p->t, m, iter, r);
}