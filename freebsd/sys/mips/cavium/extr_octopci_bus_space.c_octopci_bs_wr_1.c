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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int bus_space_handle_t ;
typedef  int bus_size_t ;
typedef  int bus_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  wr8 (int,int /*<<< orphan*/ ) ; 

void
octopci_bs_wr_1(void *t, bus_space_handle_t bsh,
    bus_size_t offset, const uint8_t *addr, size_t count)
{
	bus_addr_t baddr = bsh + offset;

	while (count--) {
		wr8(baddr, *addr++);
		baddr += 1;
	}
}