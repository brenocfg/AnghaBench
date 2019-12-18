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

/* Variables and functions */
 scalar_t__ ALTERA_JTAG_UART_DATA_OFF ; 
 scalar_t__ CHERI_UART_BASE ; 
 int /*<<< orphan*/  mips_ioread_uint32le (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mips_phys_to_uncached (scalar_t__) ; 

__attribute__((used)) static inline uint32_t
uart_data_read(void)
{

	return (mips_ioread_uint32le(mips_phys_to_uncached(CHERI_UART_BASE +
	    ALTERA_JTAG_UART_DATA_OFF)));
}