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
struct tablePart {int type; int colorColumn; TYPE_1__* tv; int /*<<< orphan*/  valueColumn; int /*<<< orphan*/  textColumn; int /*<<< orphan*/  imageColumn; } ;
typedef  scalar_t__ gpointer ;
typedef  int /*<<< orphan*/  gchar ;
struct TYPE_2__ {int backgroundColumn; int /*<<< orphan*/  treeWidget; } ;
typedef  int /*<<< orphan*/  GtkTreeViewColumn ;
typedef  int /*<<< orphan*/  GtkTreeModel ;
typedef  int /*<<< orphan*/  GtkTreeIter ;
typedef  int /*<<< orphan*/  GtkCellRenderer ;
typedef  int /*<<< orphan*/  GValue ;

/* Variables and functions */
 int /*<<< orphan*/  G_VALUE_INIT ; 
 int /*<<< orphan*/  applyColor (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  g_object_set (int /*<<< orphan*/ *,char*,int,char*,...) ; 
 int g_value_get_int (int /*<<< orphan*/ *) ; 
 scalar_t__ g_value_get_pointer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_value_get_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_value_unset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_tree_model_get_value (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
#define  partButton 132 
#define  partCheckbox 131 
#define  partImage 130 
#define  partProgressBar 129 
#define  partText 128 
 int /*<<< orphan*/  uiprivImageAppropriateSurface (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dataFunc(GtkTreeViewColumn *c, GtkCellRenderer *r, GtkTreeModel *mm, GtkTreeIter *iter, gpointer data)
{
	struct tablePart *part = (struct tablePart *) data;
	GValue value = G_VALUE_INIT;
	const gchar *str;
	uiImage *img;
	int pval;

	switch (part->type) {
	case partText:
		gtk_tree_model_get_value(mm, iter, part->textColumn, &value);
		str = g_value_get_string(&value);
		g_object_set(r, "text", str, NULL);
		if (part->colorColumn != -1)
			applyColor(mm, iter,
				part->colorColumn,
				r, "foreground-rgba", "foreground-set");
		break;
	case partImage:
//TODO		setImageSize(r);
		gtk_tree_model_get_value(mm, iter, part->imageColumn, &value);
		img = (uiImage *) g_value_get_pointer(&value);
		g_object_set(r, "surface",
			uiprivImageAppropriateSurface(img, part->tv->treeWidget),
			NULL);
		break;
	case partButton:
		gtk_tree_model_get_value(mm, iter, part->textColumn, &value);
		str = g_value_get_string(&value);
		g_object_set(r, "text", str, NULL);
		break;
	case partCheckbox:
		gtk_tree_model_get_value(mm, iter, part->valueColumn, &value);
		g_object_set(r, "active", g_value_get_int(&value) != 0, NULL);
		break;
	case partProgressBar:
		gtk_tree_model_get_value(mm, iter, part->valueColumn, &value);
		pval = g_value_get_int(&value);
		if (pval == -1) {
			// TODO
		} else
			g_object_set(r,
				"pulse", -1,
				"value", pval,
				NULL);
		break;
	}
	g_value_unset(&value);

	if (part->tv->backgroundColumn != -1)
		applyColor(mm, iter,
			part->tv->backgroundColumn,
			r, "cell-background-rgba", "cell-background-set");
}