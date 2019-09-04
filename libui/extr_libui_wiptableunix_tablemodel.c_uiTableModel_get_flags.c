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
typedef  int /*<<< orphan*/  GtkTreeModelFlags ;
typedef  int /*<<< orphan*/  GtkTreeModel ;

/* Variables and functions */
 int /*<<< orphan*/  GTK_TREE_MODEL_LIST_ONLY ; 

__attribute__((used)) static GtkTreeModelFlags uiTableModel_get_flags(GtkTreeModel *mb)
{
	return GTK_TREE_MODEL_LIST_ONLY;
}