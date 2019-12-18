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
struct vfsconf {int dummy; } ;
struct pfs_node {int dummy; } ;
struct pfs_info {int (* pi_init ) (struct pfs_info*,struct vfsconf*) ;char* pi_name; struct pfs_node* pi_root; } ;

/* Variables and functions */
 scalar_t__ bootverbose ; 
 struct pfs_node* pfs_alloc_node (struct pfs_info*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfs_destroy (struct pfs_node*) ; 
 int /*<<< orphan*/  pfs_fileno_alloc (struct pfs_node*) ; 
 int /*<<< orphan*/  pfs_fileno_init (struct pfs_info*) ; 
 int /*<<< orphan*/  pfs_fixup_dir (struct pfs_node*) ; 
 int /*<<< orphan*/  pfstype_root ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int stub1 (struct pfs_info*,struct vfsconf*) ; 

int
pfs_init(struct pfs_info *pi, struct vfsconf *vfc)
{
	struct pfs_node *root;
	int error;

	pfs_fileno_init(pi);

	/* set up the root directory */
	root = pfs_alloc_node(pi, "/", pfstype_root);
	pi->pi_root = root;
	pfs_fileno_alloc(root);
	pfs_fixup_dir(root);

	/* construct file hierarchy */
	error = (pi->pi_init)(pi, vfc);
	if (error) {
		pfs_destroy(root);
		pi->pi_root = NULL;
		return (error);
	}

	if (bootverbose)
		printf("%s registered\n", pi->pi_name);
	return (0);
}