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
typedef  int /*<<< orphan*/  bus_space_tag_t ;
typedef  int /*<<< orphan*/  bus_space_handle_t ;
typedef  scalar_t__ bus_size_t ;

/* Variables and functions */
 int bus_space_read_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static __inline uint64_t
ioat_bus_space_read_8_lower_first(bus_space_tag_t tag,
    bus_space_handle_t handle, bus_size_t offset)
{
	return (bus_space_read_4(tag, handle, offset) |
	    ((uint64_t)bus_space_read_4(tag, handle, offset + 4)) << 32);
}