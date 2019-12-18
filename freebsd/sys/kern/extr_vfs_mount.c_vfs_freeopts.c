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
struct vfsoptlist {int dummy; } ;
struct vfsopt {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_MOUNT ; 
 int /*<<< orphan*/  TAILQ_EMPTY (struct vfsoptlist*) ; 
 struct vfsopt* TAILQ_FIRST (struct vfsoptlist*) ; 
 int /*<<< orphan*/  free (struct vfsoptlist*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_freeopt (struct vfsoptlist*,struct vfsopt*) ; 

void
vfs_freeopts(struct vfsoptlist *opts)
{
	struct vfsopt *opt;

	while (!TAILQ_EMPTY(opts)) {
		opt = TAILQ_FIRST(opts);
		vfs_freeopt(opts, opt);
	}
	free(opts, M_MOUNT);
}