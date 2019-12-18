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
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  INNOVATOR_FPGA_IMR2 ; 
 int /*<<< orphan*/  INNOVATOR_FPGA_ISR2 ; 
 int /*<<< orphan*/  OMAP1510_FPGA_IMR_HI ; 
 int /*<<< orphan*/  OMAP1510_FPGA_IMR_LO ; 
 int /*<<< orphan*/  OMAP1510_FPGA_ISR_HI ; 
 int /*<<< orphan*/  OMAP1510_FPGA_ISR_LO ; 
 int __raw_readb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u32 get_fpga_unmasked_irqs(void)
{
	return
		((__raw_readb(OMAP1510_FPGA_ISR_LO) &
		  __raw_readb(OMAP1510_FPGA_IMR_LO))) |
		((__raw_readb(OMAP1510_FPGA_ISR_HI) &
		  __raw_readb(OMAP1510_FPGA_IMR_HI)) << 8) |
		((__raw_readb(INNOVATOR_FPGA_ISR2) &
		  __raw_readb(INNOVATOR_FPGA_IMR2)) << 16);
}