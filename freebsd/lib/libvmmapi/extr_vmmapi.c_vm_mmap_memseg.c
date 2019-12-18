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
typedef  scalar_t__ vm_paddr_t ;
typedef  scalar_t__ vm_ooffset_t ;
struct vmctx {int memflags; int /*<<< orphan*/  fd; } ;
struct vm_memmap {scalar_t__ gpa; int segid; scalar_t__ segoff; size_t len; int prot; int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  EEXIST ; 
 int VM_MEMMAP_F_WIRED ; 
 int VM_MEM_F_WIRED ; 
 int /*<<< orphan*/  VM_MMAP_MEMSEG ; 
 int /*<<< orphan*/  errno ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vm_memmap*) ; 
 int vm_mmap_getnext (struct vmctx*,scalar_t__*,int*,scalar_t__*,size_t*,int*,int*) ; 

int
vm_mmap_memseg(struct vmctx *ctx, vm_paddr_t gpa, int segid, vm_ooffset_t off,
    size_t len, int prot)
{
	struct vm_memmap memmap;
	int error, flags;

	memmap.gpa = gpa;
	memmap.segid = segid;
	memmap.segoff = off;
	memmap.len = len;
	memmap.prot = prot;
	memmap.flags = 0;

	if (ctx->memflags & VM_MEM_F_WIRED)
		memmap.flags |= VM_MEMMAP_F_WIRED;

	/*
	 * If this mapping already exists then don't create it again. This
	 * is the common case for SYSMEM mappings created by bhyveload(8).
	 */
	error = vm_mmap_getnext(ctx, &gpa, &segid, &off, &len, &prot, &flags);
	if (error == 0 && gpa == memmap.gpa) {
		if (segid != memmap.segid || off != memmap.segoff ||
		    prot != memmap.prot || flags != memmap.flags) {
			errno = EEXIST;
			return (-1);
		} else {
			return (0);
		}
	}

	error = ioctl(ctx->fd, VM_MMAP_MEMSEG, &memmap);
	return (error);
}