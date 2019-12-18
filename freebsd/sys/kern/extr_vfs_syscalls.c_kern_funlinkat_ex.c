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
typedef  int /*<<< orphan*/  ino_t ;
typedef  enum uio_seg { ____Placeholder_uio_seg } uio_seg ;

/* Variables and functions */
 int AT_REMOVEDIR ; 
 int EINVAL ; 
 int /*<<< orphan*/  UIO_USERSPACE ; 
 int kern_frmdirat (struct thread*,int,char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int kern_funlinkat (struct thread*,int,char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
kern_funlinkat_ex(struct thread *td, int dfd, const char *path, int fd,
    int flag, enum uio_seg pathseg, ino_t oldinum)
{

	if ((flag & ~AT_REMOVEDIR) != 0)
		return (EINVAL);

	if ((flag & AT_REMOVEDIR) != 0)
		return (kern_frmdirat(td, dfd, path, fd, UIO_USERSPACE, 0));

	return (kern_funlinkat(td, dfd, path, fd, UIO_USERSPACE, 0, 0));
}