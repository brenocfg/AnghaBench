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
struct vmctx {int /*<<< orphan*/  fd; } ;
struct vm_memseg {size_t len; int segid; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENAMETOOLONG ; 
 int /*<<< orphan*/  VM_ALLOC_MEMSEG ; 
 int /*<<< orphan*/  VM_MEMSEG_NAME (struct vm_memseg*) ; 
 int /*<<< orphan*/  bzero (struct vm_memseg*,int) ; 
 scalar_t__ cmpseg (size_t,char const*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vm_memseg*) ; 
 size_t strlcpy (int /*<<< orphan*/ ,char const*,int) ; 
 int vm_get_memseg (struct vmctx*,int,size_t*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
vm_alloc_memseg(struct vmctx *ctx, int segid, size_t len, const char *name)
{
	struct vm_memseg memseg;
	size_t n;
	int error;

	/*
	 * If the memory segment has already been created then just return.
	 * This is the usual case for the SYSMEM segment created by userspace
	 * loaders like bhyveload(8).
	 */
	error = vm_get_memseg(ctx, segid, &memseg.len, memseg.name,
	    sizeof(memseg.name));
	if (error)
		return (error);

	if (memseg.len != 0) {
		if (cmpseg(len, name, memseg.len, VM_MEMSEG_NAME(&memseg))) {
			errno = EINVAL;
			return (-1);
		} else {
			return (0);
		}
	}

	bzero(&memseg, sizeof(struct vm_memseg));
	memseg.segid = segid;
	memseg.len = len;
	if (name != NULL) {
		n = strlcpy(memseg.name, name, sizeof(memseg.name));
		if (n >= sizeof(memseg.name)) {
			errno = ENAMETOOLONG;
			return (-1);
		}
	}

	error = ioctl(ctx->fd, VM_ALLOC_MEMSEG, &memseg);
	return (error);
}