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
 int FDT_ERR_NOSPACE ; 
 int /*<<< orphan*/  devp_offset (void const*) ; 
 int /*<<< orphan*/  expand_buf (scalar_t__) ; 
 int /*<<< orphan*/  fdt ; 
 int fdt_add_subnode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 void* offset_devp (int) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static void *fdt_wrapper_create_node(const void *devp, const char *name)
{
	int offset;

	offset = fdt_add_subnode(fdt, devp_offset(devp), name);
	if (offset == -FDT_ERR_NOSPACE) {
		expand_buf(strlen(name) + 16);
		offset = fdt_add_subnode(fdt, devp_offset(devp), name);
	}

	return offset_devp(offset);
}