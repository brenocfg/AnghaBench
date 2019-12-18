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
struct vie {int reg; int mod; } ;
typedef  int /*<<< orphan*/  mem_region_write_t ;
typedef  int (* mem_region_read_t ) (void*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,void*) ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int
emulate_twob_group15(void *vm, int vcpuid, uint64_t gpa, struct vie *vie,
    mem_region_read_t memread, mem_region_write_t memwrite, void *memarg)
{
	int error;
	uint64_t buf;

	switch (vie->reg & 7) {
	case 0x7:	/* CLFLUSH, CLFLUSHOPT, and SFENCE */
		if (vie->mod == 0x3) {
			/*
			 * SFENCE.  Ignore it, VM exit provides enough
			 * barriers on its own.
			 */
			error = 0;
		} else {
			/*
			 * CLFLUSH, CLFLUSHOPT.  Only check for access
			 * rights.
			 */
			error = memread(vm, vcpuid, gpa, &buf, 1, memarg);
		}
		break;
	default:
		error = EINVAL;
		break;
	}

	return (error);
}