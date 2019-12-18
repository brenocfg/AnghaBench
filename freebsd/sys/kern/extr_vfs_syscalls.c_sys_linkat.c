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
struct thread {int dummy; } ;
struct linkat_args {int flag; int /*<<< orphan*/  path2; int /*<<< orphan*/  path1; int /*<<< orphan*/  fd2; int /*<<< orphan*/  fd1; } ;

/* Variables and functions */
 int AT_BENEATH ; 
 int AT_SYMLINK_FOLLOW ; 
 int BENEATH ; 
 int EINVAL ; 
 int FOLLOW ; 
 int NOFOLLOW ; 
 int /*<<< orphan*/  UIO_USERSPACE ; 
 int kern_linkat (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int
sys_linkat(struct thread *td, struct linkat_args *uap)
{
	int flag;

	flag = uap->flag;
	if ((flag & ~(AT_SYMLINK_FOLLOW | AT_BENEATH)) != 0)
		return (EINVAL);

	return (kern_linkat(td, uap->fd1, uap->fd2, uap->path1, uap->path2,
	    UIO_USERSPACE, ((flag & AT_SYMLINK_FOLLOW) != 0 ? FOLLOW :
	    NOFOLLOW) | ((flag & AT_BENEATH) != 0 ? BENEATH : 0)));
}