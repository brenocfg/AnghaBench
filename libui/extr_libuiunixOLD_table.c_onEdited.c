#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_4__* mh; } ;
typedef  TYPE_2__ uiTableModel ;
struct tablePart {TYPE_1__* tv; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* SetCellValue ) (TYPE_4__*,TYPE_2__*,int,int,void const*) ;} ;
struct TYPE_6__ {TYPE_2__* model; } ;
typedef  int /*<<< orphan*/  GtkTreePath ;

/* Variables and functions */
 int /*<<< orphan*/  gtk_tree_path_free (int /*<<< orphan*/ *) ; 
 int* gtk_tree_path_get_indices (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gtk_tree_path_new_from_string (char const*) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,TYPE_2__*,int,int,void const*) ; 
 int /*<<< orphan*/  uiTableModelRowChanged (TYPE_2__*,int) ; 

__attribute__((used)) static void onEdited(struct tablePart *part, int column, const char *pathstr, const void *data)
{
	GtkTreePath *path;
	int row;
	uiTableModel *m;

	path = gtk_tree_path_new_from_string(pathstr);
	row = gtk_tree_path_get_indices(path)[0];
	gtk_tree_path_free(path);
	m = part->tv->model;
	(*(m->mh->SetCellValue))(m->mh, m, row, column, data);
	// and update
	uiTableModelRowChanged(m, row);
}