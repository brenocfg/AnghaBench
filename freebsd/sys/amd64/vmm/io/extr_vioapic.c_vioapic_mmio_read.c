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
struct vioapic {int dummy; } ;

/* Variables and functions */
 int vioapic_mmio_rw (struct vioapic*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 
 struct vioapic* vm_ioapic (void*) ; 

int
vioapic_mmio_read(void *vm, int vcpuid, uint64_t gpa, uint64_t *rval,
    int size, void *arg)
{
	int error;
	struct vioapic *vioapic;

	vioapic = vm_ioapic(vm);
	error = vioapic_mmio_rw(vioapic, vcpuid, gpa, rval, size, true);
	return (error);
}