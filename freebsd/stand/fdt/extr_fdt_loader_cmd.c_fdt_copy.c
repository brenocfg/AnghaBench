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
typedef  int /*<<< orphan*/  vm_offset_t ;

/* Variables and functions */
 int /*<<< orphan*/  COPYIN (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  debugf (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ fdt_fixup () ; 
 int fdt_setup_fdtp () ; 
 int /*<<< orphan*/ * fdtp ; 
 int fdtp_size ; 
 int /*<<< orphan*/  printf (char*) ; 

int
fdt_copy(vm_offset_t va)
{
	int err;
	debugf("fdt_copy va 0x%08x\n", va);
	if (fdtp == NULL) {
		err = fdt_setup_fdtp();
		if (err) {
			printf("No valid device tree blob found!\n");
			return (0);
		}
	}

	if (fdt_fixup() == 0)
		return (0);

	COPYIN(fdtp, va, fdtp_size);
	return (fdtp_size);
}