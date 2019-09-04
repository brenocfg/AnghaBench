#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  gboolean ;
struct TYPE_4__ {int /*<<< orphan*/  stamp; } ;
typedef  int /*<<< orphan*/  GtkTreeModel ;
typedef  TYPE_1__ GtkTreeIter ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  STAMP_BAD ; 

gboolean uiTableModel_iter_parent(GtkTreeModel *mm, GtkTreeIter *iter, GtkTreeIter *child)
{
	iter->stamp = STAMP_BAD;
	return FALSE;
}