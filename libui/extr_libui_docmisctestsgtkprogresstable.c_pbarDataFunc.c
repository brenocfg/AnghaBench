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
typedef  int /*<<< orphan*/  GtkTreeViewColumn ;
typedef  int /*<<< orphan*/  GtkTreeModel ;
typedef  int /*<<< orphan*/  GtkTreeIter ;
typedef  int /*<<< orphan*/  GtkCellRenderer ;

/* Variables and functions */
 int G_MAXINT ; 
 int /*<<< orphan*/  g_object_set (int /*<<< orphan*/ *,char*,int,char*,...) ; 
 int /*<<< orphan*/  pbarStarted ; 
 int pbarValue ; 

__attribute__((used)) static void pbarDataFunc(GtkTreeViewColumn *col, GtkCellRenderer *r, GtkTreeModel *m, GtkTreeIter *iter, gpointer data)
{
	if (!pbarStarted) {
		g_object_set(r,
			"pulse", -1,
			"value", 0,
			NULL);
		return;
	}
	pbarValue++;
	if (pbarValue == G_MAXINT)
		pbarValue = 1;
	g_object_set(r, "pulse", pbarValue, NULL);
}