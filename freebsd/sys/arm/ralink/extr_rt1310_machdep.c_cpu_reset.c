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
typedef  int /*<<< orphan*/  bus_space_tag_t ;
typedef  int /*<<< orphan*/  bus_space_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  bus_space_map (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_space_unmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bus_space_write_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  fdtbus_bs_tag ; 

void
cpu_reset(void)
{
	bus_space_tag_t bst;
	bus_space_handle_t bsh;

	bst = fdtbus_bs_tag;

	/* Enable WDT */
	/* Instant assert of RESETOUT_N with pulse length 1ms */
	bus_space_map(bst, 0x1e8c0000, 0x20000, 0, &bsh);
	bus_space_write_4(bst, bsh, 0, 13000);
	bus_space_write_4(bst, bsh, 8, (1<<3) | (1<<4) | 7);
	bus_space_unmap(bst, bsh, 0x20000);

	for (;;)
		continue;
}