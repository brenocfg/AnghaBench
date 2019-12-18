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
typedef  scalar_t__ bus_space_tag_t ;
typedef  int /*<<< orphan*/  bus_space_handle_t ;
typedef  int /*<<< orphan*/  bus_size_t ;

/* Variables and functions */
 scalar_t__ X86_BUS_SPACE_MEM ; 
 int /*<<< orphan*/  pmap_unmapdev (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
bus_space_unmap(bus_space_tag_t tag, bus_space_handle_t bsh, bus_size_t size)
{

	if (tag == X86_BUS_SPACE_MEM)
		pmap_unmapdev(bsh, size);
}