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
struct mqfs_node {int mn_type; int /*<<< orphan*/  mn_fileno; } ;
struct mqfs_info {int /*<<< orphan*/  mi_unrhdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free_unr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  mqfstype_dir 133 
#define  mqfstype_file 132 
#define  mqfstype_parent 131 
#define  mqfstype_root 130 
#define  mqfstype_symlink 129 
#define  mqfstype_this 128 

__attribute__((used)) static void
mqfs_fileno_free(struct mqfs_info *mi, struct mqfs_node *mn)
{
	switch (mn->mn_type) {
	case mqfstype_root:
	case mqfstype_dir:
	case mqfstype_file:
	case mqfstype_symlink:
		free_unr(mi->mi_unrhdr, mn->mn_fileno);
		break;
	case mqfstype_this:
	case mqfstype_parent:
		/* ignore these, as they don't "own" their file number */
		break;
	default:
		KASSERT(0,
		    ("mqfs_fileno_free() called for unknown type node: %d", 
			mn->mn_type));
		break;
	}
}