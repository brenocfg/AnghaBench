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
struct uio {int dummy; } ;
struct thread {int dummy; } ;
struct freebsd32_nmount_args {int iovcnt; int /*<<< orphan*/  iovp; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_ARG_FFLAGS (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  MNT_ROOTFS ; 
 int /*<<< orphan*/  M_IOV ; 
 int /*<<< orphan*/  free (struct uio*,int /*<<< orphan*/ ) ; 
 int freebsd32_copyinuio (int /*<<< orphan*/ ,int,struct uio**) ; 
 int vfs_donmount (struct thread*,int /*<<< orphan*/ ,struct uio*) ; 

int
freebsd32_nmount(struct thread *td,
    struct freebsd32_nmount_args /* {
    	struct iovec *iovp;
    	unsigned int iovcnt;
    	int flags;
    } */ *uap)
{
	struct uio *auio;
	uint64_t flags;
	int error;

	/*
	 * Mount flags are now 64-bits. On 32-bit archtectures only
	 * 32-bits are passed in, but from here on everything handles
	 * 64-bit flags correctly.
	 */
	flags = uap->flags;

	AUDIT_ARG_FFLAGS(flags);

	/*
	 * Filter out MNT_ROOTFS.  We do not want clients of nmount() in
	 * userspace to set this flag, but we must filter it out if we want
	 * MNT_UPDATE on the root file system to work.
	 * MNT_ROOTFS should only be set by the kernel when mounting its
	 * root file system.
	 */
	flags &= ~MNT_ROOTFS;

	/*
	 * check that we have an even number of iovec's
	 * and that we have at least two options.
	 */
	if ((uap->iovcnt & 1) || (uap->iovcnt < 4))
		return (EINVAL);

	error = freebsd32_copyinuio(uap->iovp, uap->iovcnt, &auio);
	if (error)
		return (error);
	error = vfs_donmount(td, flags, auio);

	free(auio, M_IOV);
	return error;
}