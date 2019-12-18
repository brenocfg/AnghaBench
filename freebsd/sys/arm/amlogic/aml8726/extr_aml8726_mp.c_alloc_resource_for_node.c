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
typedef  scalar_t__ u_long ;
struct resource {int /*<<< orphan*/  r_bushandle; int /*<<< orphan*/  r_bustag; } ;
typedef  int /*<<< orphan*/  phandle_t ;

/* Variables and functions */
 int /*<<< orphan*/  OF_parent (int /*<<< orphan*/ ) ; 
 int bus_space_map (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int fdt_get_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,scalar_t__*) ; 
 int fdt_regsize (int /*<<< orphan*/ ,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  fdtbus_bs_tag ; 
 int /*<<< orphan*/  memset (struct resource*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
alloc_resource_for_node(phandle_t node, struct resource *res, u_long *size)
{
	int err;
	u_long pbase, psize;
	u_long start;

	if ((err = fdt_get_range(OF_parent(node), 0, &pbase, &psize)) != 0 ||
	    (err = fdt_regsize(node, &start, size)) != 0)
		return (err);

	start += pbase;

	memset(res, 0, sizeof(*res));

	res->r_bustag = fdtbus_bs_tag;

	err = bus_space_map(res->r_bustag, start, *size, 0, &res->r_bushandle);

	return (err);
}