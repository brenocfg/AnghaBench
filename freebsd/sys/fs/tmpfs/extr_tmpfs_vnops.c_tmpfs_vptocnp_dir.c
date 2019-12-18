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
struct tmpfs_node {int dummy; } ;
struct tmpfs_dirent {struct tmpfs_node* td_node; } ;
struct tmpfs_dir_cursor {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 struct tmpfs_dirent* tmpfs_dir_first (struct tmpfs_node*,struct tmpfs_dir_cursor*) ; 
 struct tmpfs_dirent* tmpfs_dir_next (struct tmpfs_node*,struct tmpfs_dir_cursor*) ; 

__attribute__((used)) static int
tmpfs_vptocnp_dir(struct tmpfs_node *tn, struct tmpfs_node *tnp,
    struct tmpfs_dirent **pde)
{
	struct tmpfs_dir_cursor dc;
	struct tmpfs_dirent *de;

	for (de = tmpfs_dir_first(tnp, &dc); de != NULL;
	     de = tmpfs_dir_next(tnp, &dc)) {
		if (de->td_node == tn) {
			*pde = de;
			return (0);
		}
	}
	return (ENOENT);
}