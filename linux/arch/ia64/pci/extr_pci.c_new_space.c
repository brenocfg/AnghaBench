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
typedef  scalar_t__ u64 ;
struct TYPE_2__ {scalar_t__ mmio_base; int sparse; } ;

/* Variables and functions */
 int MAX_IO_SPACES ; 
 TYPE_1__* io_space ; 
 scalar_t__ ioremap (scalar_t__,int /*<<< orphan*/ ) ; 
 int num_io_spaces ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 

__attribute__((used)) static unsigned int new_space(u64 phys_base, int sparse)
{
	u64 mmio_base;
	int i;

	if (phys_base == 0)
		return 0;	/* legacy I/O port space */

	mmio_base = (u64) ioremap(phys_base, 0);
	for (i = 0; i < num_io_spaces; i++)
		if (io_space[i].mmio_base == mmio_base &&
		    io_space[i].sparse == sparse)
			return i;

	if (num_io_spaces == MAX_IO_SPACES) {
		pr_err("PCI: Too many IO port spaces "
			"(MAX_IO_SPACES=%lu)\n", MAX_IO_SPACES);
		return ~0;
	}

	i = num_io_spaces++;
	io_space[i].mmio_base = mmio_base;
	io_space[i].sparse = sparse;

	return i;
}