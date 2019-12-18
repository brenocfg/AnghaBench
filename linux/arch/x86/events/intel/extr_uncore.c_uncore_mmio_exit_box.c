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
struct intel_uncore_box {scalar_t__ io_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  iounmap (scalar_t__) ; 

void uncore_mmio_exit_box(struct intel_uncore_box *box)
{
	if (box->io_addr)
		iounmap(box->io_addr);
}