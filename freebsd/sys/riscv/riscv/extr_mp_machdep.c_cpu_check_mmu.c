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
typedef  int /*<<< orphan*/  u_int ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/  pcell_t ;
typedef  int boolean_t ;

/* Variables and functions */
 scalar_t__ OF_getproplen (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static boolean_t
cpu_check_mmu(u_int id, phandle_t node, u_int addr_size, pcell_t *reg)
{

	/* Check if this hart supports MMU. */
	if (OF_getproplen(node, "mmu-type") < 0)
		return (0);

	return (1);
}