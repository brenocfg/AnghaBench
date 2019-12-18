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
struct TYPE_3__ {int /*<<< orphan*/  tv; } ;
typedef  TYPE_1__ uiTable ;
typedef  int /*<<< orphan*/  GtkTreeViewColumn ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  gtk_tree_view_append_column (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gtk_tree_view_column_new () ; 
 int /*<<< orphan*/  gtk_tree_view_column_set_resizable (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_tree_view_column_set_title (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static GtkTreeViewColumn *addColumn(uiTable *t, const char *name)
{
	GtkTreeViewColumn *c;

	c = gtk_tree_view_column_new();
	gtk_tree_view_column_set_resizable(c, TRUE);
	gtk_tree_view_column_set_title(c, name);
	gtk_tree_view_append_column(t->tv, c);
	return c;
}