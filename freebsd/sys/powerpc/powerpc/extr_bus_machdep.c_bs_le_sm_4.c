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
typedef  int /*<<< orphan*/  bus_space_handle_t ;
typedef  int /*<<< orphan*/  bus_size_t ;

/* Variables and functions */
 int /*<<< orphan*/ * __ppc_ba (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  out32rb (int /*<<< orphan*/  volatile*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  powerpc_iomb () ; 

__attribute__((used)) static void
bs_le_sm_4(bus_space_handle_t bsh, bus_size_t ofs, uint32_t val, size_t cnt)
{
	volatile uint32_t *d = __ppc_ba(bsh, ofs);

	while (cnt--)
		out32rb(d, val);
	powerpc_iomb();
}