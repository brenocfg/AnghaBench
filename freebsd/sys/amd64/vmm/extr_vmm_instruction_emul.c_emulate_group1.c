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
struct vm_guest_paging {int dummy; } ;
struct vie {int reg; } ;
typedef  int /*<<< orphan*/  mem_region_write_t ;
typedef  int /*<<< orphan*/  mem_region_read_t ;

/* Variables and functions */
 int EINVAL ; 
 int emulate_and (void*,int,int /*<<< orphan*/ ,struct vie*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int emulate_cmp (void*,int,int /*<<< orphan*/ ,struct vie*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int emulate_or (void*,int,int /*<<< orphan*/ ,struct vie*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static int
emulate_group1(void *vm, int vcpuid, uint64_t gpa, struct vie *vie,
    struct vm_guest_paging *paging, mem_region_read_t memread,
    mem_region_write_t memwrite, void *memarg)
{
	int error;

	switch (vie->reg & 7) {
	case 0x1:	/* OR */
		error = emulate_or(vm, vcpuid, gpa, vie,
		    memread, memwrite, memarg);
		break;
	case 0x4:	/* AND */
		error = emulate_and(vm, vcpuid, gpa, vie,
		    memread, memwrite, memarg);
		break;
	case 0x7:	/* CMP */
		error = emulate_cmp(vm, vcpuid, gpa, vie,
		    memread, memwrite, memarg);
		break;
	default:
		error = EINVAL;
		break;
	}

	return (error);
}