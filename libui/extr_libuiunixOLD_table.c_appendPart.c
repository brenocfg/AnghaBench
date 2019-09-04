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
struct TYPE_3__ {int /*<<< orphan*/  parts; int /*<<< orphan*/  c; } ;
typedef  TYPE_1__ uiTableColumn ;
struct tablePart {int /*<<< orphan*/ * r; } ;
typedef  int /*<<< orphan*/  GtkCellRenderer ;

/* Variables and functions */
 int /*<<< orphan*/  dataFunc ; 
 int /*<<< orphan*/  g_ptr_array_add (int /*<<< orphan*/ ,struct tablePart*) ; 
 int /*<<< orphan*/  gtk_tree_view_column_pack_start (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  gtk_tree_view_column_set_cell_data_func (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct tablePart*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void appendPart(uiTableColumn *c, struct tablePart *part, GtkCellRenderer *r, int expand)
{
	part->r = r;
	gtk_tree_view_column_pack_start(c->c, part->r, expand != 0);
	gtk_tree_view_column_set_cell_data_func(c->c, part->r, dataFunc, part, NULL);
	g_ptr_array_add(c->parts, part);
}