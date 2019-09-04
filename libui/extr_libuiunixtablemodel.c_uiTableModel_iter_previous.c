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
typedef  scalar_t__ gint ;
typedef  int /*<<< orphan*/  gboolean ;
struct TYPE_3__ {scalar_t__ stamp; int /*<<< orphan*/  user_data; } ;
typedef  int /*<<< orphan*/  GtkTreeModel ;
typedef  TYPE_1__ GtkTreeIter ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GINT_TO_POINTER (scalar_t__) ; 
 scalar_t__ GPOINTER_TO_INT (int /*<<< orphan*/ ) ; 
 scalar_t__ STAMP_BAD ; 
 scalar_t__ STAMP_GOOD ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static gboolean uiTableModel_iter_previous(GtkTreeModel *mm, GtkTreeIter *iter)
{
	gint row;

	if (iter->stamp != STAMP_GOOD)
		return FALSE;
	row = GPOINTER_TO_INT(iter->user_data);
	row--;
	if (row < 0) {
		iter->stamp = STAMP_BAD;
		return FALSE;
	}
	iter->user_data = GINT_TO_POINTER(row);
	return TRUE;
}