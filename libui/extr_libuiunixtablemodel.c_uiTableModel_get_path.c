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
typedef  int /*<<< orphan*/  gint ;
struct TYPE_3__ {scalar_t__ stamp; int /*<<< orphan*/  user_data; } ;
typedef  int /*<<< orphan*/  GtkTreePath ;
typedef  int /*<<< orphan*/  GtkTreeModel ;
typedef  TYPE_1__ GtkTreeIter ;

/* Variables and functions */
 int /*<<< orphan*/  GPOINTER_TO_INT (int /*<<< orphan*/ ) ; 
 scalar_t__ STAMP_GOOD ; 
 int /*<<< orphan*/ * gtk_tree_path_new_from_indices (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static GtkTreePath *uiTableModel_get_path(GtkTreeModel *mm, GtkTreeIter  *iter)
{
	gint row;

	if (iter->stamp != STAMP_GOOD)
		return NULL;
	row = GPOINTER_TO_INT(iter->user_data);
	return gtk_tree_path_new_from_indices(row, -1);
}