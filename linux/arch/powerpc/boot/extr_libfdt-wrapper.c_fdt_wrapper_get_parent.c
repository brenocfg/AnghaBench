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

/* Variables and functions */
 int /*<<< orphan*/  devp_offset (void const*) ; 
 int /*<<< orphan*/  fdt ; 
 int /*<<< orphan*/  fdt_parent_offset (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* offset_devp (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *fdt_wrapper_get_parent(const void *devp)
{
	return offset_devp(fdt_parent_offset(fdt, devp_offset(devp)));
}