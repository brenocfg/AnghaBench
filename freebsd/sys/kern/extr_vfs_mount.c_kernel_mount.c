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
typedef  int /*<<< orphan*/  uint64_t ;
struct uio {int uio_iovcnt; int /*<<< orphan*/  uio_segflg; int /*<<< orphan*/ * uio_iov; } ;
struct mntarg {int len; int error; int /*<<< orphan*/ * v; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  UIO_SYSSPACE ; 
 int /*<<< orphan*/  curthread ; 
 int /*<<< orphan*/  free_mntarg (struct mntarg*) ; 
 int vfs_donmount (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct uio*) ; 

int
kernel_mount(struct mntarg *ma, uint64_t flags)
{
	struct uio auio;
	int error;

	KASSERT(ma != NULL, ("kernel_mount NULL ma"));
	KASSERT(ma->v != NULL, ("kernel_mount NULL ma->v"));
	KASSERT(!(ma->len & 1), ("kernel_mount odd ma->len (%d)", ma->len));

	auio.uio_iov = ma->v;
	auio.uio_iovcnt = ma->len;
	auio.uio_segflg = UIO_SYSSPACE;

	error = ma->error;
	if (!error)
		error = vfs_donmount(curthread, flags, &auio);
	free_mntarg(ma);
	return (error);
}