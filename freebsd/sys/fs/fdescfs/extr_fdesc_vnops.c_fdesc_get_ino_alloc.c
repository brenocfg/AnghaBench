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
struct vnode {int dummy; } ;
struct mount {int dummy; } ;
struct fdesc_get_ino_args {int /*<<< orphan*/  td; int /*<<< orphan*/  fp; int /*<<< orphan*/  ix; int /*<<< orphan*/  fd_fd; int /*<<< orphan*/  ftype; } ;

/* Variables and functions */
 int fdesc_allocvp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mount*,struct vnode**) ; 
 int /*<<< orphan*/  fdrop (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
fdesc_get_ino_alloc(struct mount *mp, void *arg, int lkflags,
    struct vnode **rvp)
{
	struct fdesc_get_ino_args *a;
	int error;

	a = arg;
	error = fdesc_allocvp(a->ftype, a->fd_fd, a->ix, mp, rvp);
	fdrop(a->fp, a->td);
	return (error);
}