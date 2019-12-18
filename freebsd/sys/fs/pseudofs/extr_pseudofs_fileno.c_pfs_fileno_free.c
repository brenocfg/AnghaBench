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
struct pfs_node {int pn_type; int /*<<< orphan*/  pn_fileno; TYPE_1__* pn_info; } ;
struct TYPE_2__ {int /*<<< orphan*/  pi_unrhdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free_unr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfs_assert_not_owned (struct pfs_node*) ; 
#define  pfstype_dir 135 
#define  pfstype_file 134 
#define  pfstype_none 133 
#define  pfstype_parent 132 
#define  pfstype_procdir 131 
#define  pfstype_root 130 
#define  pfstype_symlink 129 
#define  pfstype_this 128 

void
pfs_fileno_free(struct pfs_node *pn)
{

	pfs_assert_not_owned(pn);

	switch (pn->pn_type) {
	case pfstype_root:
		/* not allocated from unrhdr */
		return;
	case pfstype_dir:
	case pfstype_file:
	case pfstype_symlink:
	case pfstype_procdir:
		free_unr(pn->pn_info->pi_unrhdr, pn->pn_fileno);
		break;
	case pfstype_this:
	case pfstype_parent:
		/* ignore these, as they don't "own" their file number */
		break;
	case pfstype_none:
		KASSERT(0,
		    ("pfs_fileno_free() called for pfstype_none node"));
		break;
	}
}