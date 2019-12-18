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
struct TYPE_2__ {scalar_t__ va_type; int /*<<< orphan*/  va_nlink; } ;
struct puffs_node {TYPE_1__ pn_va; } ;
struct dtfs_mount {int /*<<< orphan*/  dtm_nfiles; } ;
struct dtfs_file {struct puffs_node* df_dotdot; int /*<<< orphan*/  df_dirents; } ;
struct dtfs_dirent {struct puffs_node* dfd_node; struct puffs_node* dfd_parent; } ;

/* Variables and functions */
 struct dtfs_file* DTFS_PTOF (struct puffs_node*) ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,struct dtfs_dirent*,int /*<<< orphan*/ ) ; 
 scalar_t__ VDIR ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  dfd_entries ; 
 int /*<<< orphan*/  dtfs_updatetimes (struct puffs_node*,int /*<<< orphan*/ ,int,int) ; 
 struct dtfs_mount* puffs_pn_getmntspecific (struct puffs_node*) ; 

void
dtfs_adddent(struct puffs_node *pn_dir, struct dtfs_dirent *dent)
{
	struct dtfs_file *dir = DTFS_PTOF(pn_dir);
	struct puffs_node *pn_file = dent->dfd_node;
	struct dtfs_file *file = DTFS_PTOF(pn_file);
	struct dtfs_mount *dtm;

	assert(pn_dir->pn_va.va_type == VDIR);
	LIST_INSERT_HEAD(&dir->df_dirents, dent, dfd_entries);
	pn_file->pn_va.va_nlink++;

	dtm = puffs_pn_getmntspecific(pn_file);
	dtm->dtm_nfiles++;

	dent->dfd_parent = pn_dir;
	if (dent->dfd_node->pn_va.va_type == VDIR) {
		file->df_dotdot = pn_dir;
		pn_dir->pn_va.va_nlink++;
	}

	dtfs_updatetimes(pn_dir, 0, 1, 1);
}