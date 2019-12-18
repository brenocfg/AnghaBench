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
struct mqfs_node {int mn_type; int /*<<< orphan*/  mn_fileno; struct mqfs_node* mn_parent; } ;
struct mqfs_info {struct mqfs_node* mi_root; int /*<<< orphan*/  mi_unrhdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  alloc_unr (int /*<<< orphan*/ ) ; 
#define  mqfstype_dir 133 
#define  mqfstype_file 132 
#define  mqfstype_parent 131 
#define  mqfstype_root 130 
#define  mqfstype_symlink 129 
#define  mqfstype_this 128 

__attribute__((used)) static void
mqfs_fileno_alloc(struct mqfs_info *mi, struct mqfs_node *mn)
{
	/* make sure our parent has a file number */
	if (mn->mn_parent && !mn->mn_parent->mn_fileno)
		mqfs_fileno_alloc(mi, mn->mn_parent);

	switch (mn->mn_type) {
	case mqfstype_root:
	case mqfstype_dir:
	case mqfstype_file:
	case mqfstype_symlink:
		mn->mn_fileno = alloc_unr(mi->mi_unrhdr);
		break;
	case mqfstype_this:
		KASSERT(mn->mn_parent != NULL,
		    ("mqfstype_this node has no parent"));
		mn->mn_fileno = mn->mn_parent->mn_fileno;
		break;
	case mqfstype_parent:
		KASSERT(mn->mn_parent != NULL,
		    ("mqfstype_parent node has no parent"));
		if (mn->mn_parent == mi->mi_root) {
			mn->mn_fileno = mn->mn_parent->mn_fileno;
			break;
		}
		KASSERT(mn->mn_parent->mn_parent != NULL,
		    ("mqfstype_parent node has no grandparent"));
		mn->mn_fileno = mn->mn_parent->mn_parent->mn_fileno;
		break;
	default:
		KASSERT(0,
		    ("mqfs_fileno_alloc() called for unknown type node: %d",
			mn->mn_type));
		break;
	}
}