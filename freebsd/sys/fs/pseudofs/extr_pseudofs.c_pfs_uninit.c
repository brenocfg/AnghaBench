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
struct pfs_info {char* pi_name; int (* pi_uninit ) (struct pfs_info*,struct vfsconf*) ;int /*<<< orphan*/ * pi_root; } ;

/* Variables and functions */
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  pfs_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pfs_fileno_uninit (struct pfs_info*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int stub1 (struct pfs_info*,struct vfsconf*) ; 

int
pfs_uninit(struct pfs_info *pi, struct vfsconf *vfc)
{
	int error;

	pfs_destroy(pi->pi_root);
	pi->pi_root = NULL;
	pfs_fileno_uninit(pi);
	if (bootverbose)
		printf("%s unregistered\n", pi->pi_name);
	error = (pi->pi_uninit)(pi, vfc);
	return (error);
}