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
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  ofw_bus_node_is_compatible (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static boolean_t
alpine_validate_cpu(u_int id, phandle_t child, u_int addr_cell, pcell_t *reg)
{
	return ofw_bus_node_is_compatible(child, "arm,cortex-a15");
}