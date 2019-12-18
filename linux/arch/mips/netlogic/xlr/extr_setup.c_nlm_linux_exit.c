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

/* Variables and functions */
 int /*<<< orphan*/  GPIO_SWRESET_REG ; 
 int /*<<< orphan*/  NETLOGIC_IO_GPIO_OFFSET ; 
 int /*<<< orphan*/  cpu_wait () ; 
 int /*<<< orphan*/  nlm_mmio_base (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlm_write_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void nlm_linux_exit(void)
{
	uint64_t gpiobase;

	gpiobase = nlm_mmio_base(NETLOGIC_IO_GPIO_OFFSET);
	/* trigger a chip reset by writing 1 to GPIO_SWRESET_REG */
	nlm_write_reg(gpiobase, GPIO_SWRESET_REG, 1);
	for ( ; ; )
		cpu_wait();
}