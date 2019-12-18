#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  size; } ;

/* Variables and functions */
 scalar_t__ fdt64_to_cpu (int /*<<< orphan*/ ) ; 
 TYPE_1__* fdt_mem_rsv_ (void const*,int) ; 

int fdt_num_mem_rsv(const void *fdt)
{
	int i = 0;

	while (fdt64_to_cpu(fdt_mem_rsv_(fdt, i)->size) != 0)
		i++;
	return i;
}