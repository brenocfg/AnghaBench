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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  phandle_t ;

/* Variables and functions */
 int /*<<< orphan*/  OF_getencprop (int /*<<< orphan*/ ,char*,int*,int) ; 

__attribute__((used)) static void
get_addr_props(phandle_t node, uint32_t *addrp, uint32_t *sizep)
{

	*addrp = 2;
	*sizep = 1;
	OF_getencprop(node, "#address-cells", addrp, sizeof(*addrp));
	OF_getencprop(node, "#size-cells", sizep, sizeof(*sizep));
}