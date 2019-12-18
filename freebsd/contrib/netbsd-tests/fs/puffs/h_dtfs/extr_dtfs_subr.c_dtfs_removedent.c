#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ va_type; int va_nlink; } ;
struct puffs_node {TYPE_1__ pn_va; } ;
struct dtfs_file {int /*<<< orphan*/ * df_dotdot; } ;
struct dtfs_dirent {struct puffs_node* dfd_node; } ;

/* Variables and functions */
 struct dtfs_file* DTFS_PTOF (struct puffs_node*) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct dtfs_dirent*,int /*<<< orphan*/ ) ; 
 scalar_t__ VDIR ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  dfd_entries ; 
 int /*<<< orphan*/  dtfs_updatetimes (struct puffs_node*,int /*<<< orphan*/ ,int,int) ; 

void
dtfs_removedent(struct puffs_node *pn_dir, struct dtfs_dirent *dent)
{
	struct puffs_node *pn_file = dent->dfd_node;

	assert(pn_dir->pn_va.va_type == VDIR);
	LIST_REMOVE(dent, dfd_entries);
	if (pn_file->pn_va.va_type == VDIR) {
		struct dtfs_file *df = DTFS_PTOF(pn_file);

		pn_dir->pn_va.va_nlink--;
		df->df_dotdot = NULL;
	}
	pn_file->pn_va.va_nlink--;
	assert(pn_dir->pn_va.va_nlink >= 2);

	dtfs_updatetimes(pn_dir, 0, 1, 1);
}