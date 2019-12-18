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
typedef  scalar_t__ bus_space_handle_t ;
typedef  scalar_t__ bus_size_t ;
typedef  scalar_t__ bus_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  rd8 (scalar_t__) ; 
 int /*<<< orphan*/  wr8 (scalar_t__,int /*<<< orphan*/ ) ; 

void
generic_bs_c_1(void *t, bus_space_handle_t bsh1,
    bus_size_t off1, bus_space_handle_t bsh2,
    bus_size_t off2, size_t count)
{
	bus_addr_t addr1 = bsh1 + off1;
	bus_addr_t addr2 = bsh2 + off2;

	if (addr1 >= addr2) {
		/* src after dest: copy forward */
		for (; count != 0; count--, addr1++, addr2++)
			wr8(addr2, rd8(addr1));
	} else {
		/* dest after src: copy backwards */
		for (addr1 += (count - 1), addr2 += (count - 1);
		    count != 0; count--, addr1--, addr2--)
			wr8(addr2, rd8(addr1));
	}
}