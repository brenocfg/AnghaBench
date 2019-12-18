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
struct textColumnParams {int /*<<< orphan*/  m; int /*<<< orphan*/  modelColumn; } ;
typedef  scalar_t__ gpointer ;
typedef  int /*<<< orphan*/  gchar ;
typedef  int /*<<< orphan*/  GtkTreeIter ;
typedef  int /*<<< orphan*/  GtkCellRendererText ;

/* Variables and functions */
 int /*<<< orphan*/  GTK_CELL_RENDERER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_TREE_MODEL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  onEdited (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  textColumnDataFunc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  uiFreeTableValue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * uiNewTableValueString (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void textColumnEdited(GtkCellRendererText *r, gchar *path, gchar *newText, gpointer data)
{
	struct textColumnParams *p = (struct textColumnParams *) data;
	uiTableValue *tvalue;
	GtkTreeIter iter;

	tvalue = uiNewTableValueString(newText);
	onEdited(p->m, p->modelColumn, path, tvalue, &iter);
	uiFreeTableValue(tvalue);
	// and update the column TODO copy comment here
	textColumnDataFunc(NULL, GTK_CELL_RENDERER(r), GTK_TREE_MODEL(p->m), &iter, data);
}