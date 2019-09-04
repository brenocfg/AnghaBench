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
struct TYPE_3__ {int /*<<< orphan*/  iter_parent; int /*<<< orphan*/  iter_nth_child; int /*<<< orphan*/  iter_n_children; int /*<<< orphan*/  iter_has_child; int /*<<< orphan*/  iter_children; int /*<<< orphan*/  iter_previous; int /*<<< orphan*/  iter_next; int /*<<< orphan*/  get_value; int /*<<< orphan*/  get_path; int /*<<< orphan*/  get_iter; int /*<<< orphan*/  get_column_type; int /*<<< orphan*/  get_n_columns; int /*<<< orphan*/  get_flags; } ;
typedef  TYPE_1__ GtkTreeModelIface ;

/* Variables and functions */
 int /*<<< orphan*/  uiTableModel_get_column_type ; 
 int /*<<< orphan*/  uiTableModel_get_flags ; 
 int /*<<< orphan*/  uiTableModel_get_iter ; 
 int /*<<< orphan*/  uiTableModel_get_n_columns ; 
 int /*<<< orphan*/  uiTableModel_get_path ; 
 int /*<<< orphan*/  uiTableModel_get_value ; 
 int /*<<< orphan*/  uiTableModel_iter_children ; 
 int /*<<< orphan*/  uiTableModel_iter_has_child ; 
 int /*<<< orphan*/  uiTableModel_iter_n_children ; 
 int /*<<< orphan*/  uiTableModel_iter_next ; 
 int /*<<< orphan*/  uiTableModel_iter_nth_child ; 
 int /*<<< orphan*/  uiTableModel_iter_parent ; 
 int /*<<< orphan*/  uiTableModel_iter_previous ; 

__attribute__((used)) static void uiTableModel_treeModel_init(GtkTreeModelIface *iface)
{
	iface->get_flags = uiTableModel_get_flags;
	iface->get_n_columns = uiTableModel_get_n_columns;
	iface->get_column_type = uiTableModel_get_column_type;
	iface->get_iter = uiTableModel_get_iter;
	iface->get_path = uiTableModel_get_path;
	iface->get_value = uiTableModel_get_value;
	iface->iter_next = uiTableModel_iter_next;
	iface->iter_previous = uiTableModel_iter_previous;
	iface->iter_children = uiTableModel_iter_children;
	iface->iter_has_child = uiTableModel_iter_has_child;
	iface->iter_n_children = uiTableModel_iter_n_children;
	iface->iter_nth_child = uiTableModel_iter_nth_child;
	iface->iter_parent = uiTableModel_iter_parent;
	// no need for ref_node or unref_node
}