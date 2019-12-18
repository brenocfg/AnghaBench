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
 int /*<<< orphan*/  COP0_BADVADDR ; 
 int /*<<< orphan*/  COP0_CAUSE ; 
 int /*<<< orphan*/  COP0_EPC ; 
 int /*<<< orphan*/  COP0_STATUS ; 
 int /*<<< orphan*/  CVMX_MF_COP0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ HI32 (int /*<<< orphan*/ ) ; 
 scalar_t__ LO32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_safe_printf (char*,int /*<<< orphan*/ ,int,unsigned int,unsigned int,int /*<<< orphan*/ ,int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  print_reg64 (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * reg_names ; 

__attribute__((used)) static void __cvmx_interrupt_dump_registers(uint64_t *registers)
{
    uint64_t r1, r2;
    int reg;
    for (reg=0; reg<16; reg++)
    {
        r1 = registers[reg]; r2 = registers[reg+16];
        cvmx_safe_printf("%3s ($%02d): 0x%08x%08x \t %3s ($%02d): 0x%08x%08x\n",
                           reg_names[reg], reg, (unsigned int)HI32(r1), (unsigned int)LO32(r1),
                           reg_names[reg+16], reg+16, (unsigned int)HI32(r2), (unsigned int)LO32(r2));
    }
    CVMX_MF_COP0 (r1, COP0_CAUSE);
    print_reg64 ("COP0_CAUSE", r1);
    CVMX_MF_COP0 (r2, COP0_STATUS);
    print_reg64 ("COP0_STATUS", r2);
    CVMX_MF_COP0 (r1, COP0_BADVADDR);
    print_reg64 ("COP0_BADVADDR", r1);
    CVMX_MF_COP0 (r2, COP0_EPC);
    print_reg64 ("COP0_EPC", r2);
}