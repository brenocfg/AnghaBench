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
typedef  int uint64_t ;
struct vlapic {int dummy; } ;

/* Variables and functions */
 int DEFAULT_APIC_BASE ; 
 int EINVAL ; 
 int vlapic_read (struct vlapic*,int,int,int*,void*) ; 
 struct vlapic* vm_lapic (void*,int) ; 

int
lapic_mmio_read(void *vm, int cpu, uint64_t gpa, uint64_t *rval, int size,
		void *arg)
{
	int error;
	uint64_t off;
	struct vlapic *vlapic;

	off = gpa - DEFAULT_APIC_BASE;

	/*
	 * Memory mapped local apic accesses should be aligned on a
	 * 16-byte boundary.  They are also suggested to be 4 bytes
	 * wide, alas not all OSes follow suggestions.
	 */
	off &= ~3;
	if (off & 0xf)
		return (EINVAL);

	vlapic = vm_lapic(vm, cpu);
	error = vlapic_read(vlapic, 1, off, rval, arg);
	return (error);
}