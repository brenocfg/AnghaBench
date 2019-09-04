#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uiImage ;
struct imageColumnParams {TYPE_1__* t; int /*<<< orphan*/  modelColumn; } ;
typedef  scalar_t__ gpointer ;
struct TYPE_2__ {int /*<<< orphan*/  treeWidget; } ;
typedef  int /*<<< orphan*/  GtkTreeViewColumn ;
typedef  int /*<<< orphan*/  GtkTreeModel ;
typedef  int /*<<< orphan*/  GtkTreeIter ;
typedef  int /*<<< orphan*/  GtkCellRenderer ;
typedef  int /*<<< orphan*/  GValue ;

/* Variables and functions */
 int /*<<< orphan*/  G_VALUE_INIT ; 
 int /*<<< orphan*/  applyBackgroundColor (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_object_set (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ g_value_get_pointer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_value_unset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_tree_model_get_value (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiprivImageAppropriateSurface (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void imageColumnDataFunc(GtkTreeViewColumn *c, GtkCellRenderer *r, GtkTreeModel *m, GtkTreeIter *iter, gpointer data)
{
	struct imageColumnParams *p = (struct imageColumnParams *) data;
	GValue value = G_VALUE_INIT;
	uiImage *img;

//TODO	setImageSize(r);
	gtk_tree_model_get_value(m, iter, p->modelColumn, &value);
	img = (uiImage *) g_value_get_pointer(&value);
	g_object_set(r, "surface",
		uiprivImageAppropriateSurface(img, p->t->treeWidget),
		NULL);
	g_value_unset(&value);

	applyBackgroundColor(p->t, m, iter, r);
}