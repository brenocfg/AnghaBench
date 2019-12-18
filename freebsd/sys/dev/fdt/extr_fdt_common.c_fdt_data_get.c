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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  u_long ;

/* Variables and functions */
 int /*<<< orphan*/  fdt32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fdt64_to_cpu (int /*<<< orphan*/ ) ; 

u_long
fdt_data_get(void *data, int cells)
{

	if (cells == 1)
		return (fdt32_to_cpu(*((uint32_t *)data)));

	return (fdt64_to_cpu(*((uint64_t *)data)));
}