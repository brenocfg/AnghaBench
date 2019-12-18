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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  u_int32_t ;
typedef  scalar_t__ bus_space_handle_t ;
typedef  scalar_t__ bus_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  bswap32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u_int32_t
rmi_pci_bus_space_read_4(void *tag, bus_space_handle_t handle,
    bus_size_t offset)
{
	uint32_t value;

	value = *(volatile u_int32_t *)(handle + offset);
	return bswap32(value);
}