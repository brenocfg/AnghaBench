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

/* Variables and functions */
 int /*<<< orphan*/  CAUSEF_IV ; 
 int MIPS_EBASE_WG ; 
 int /*<<< orphan*/  ST0_BEV ; 
 int /*<<< orphan*/  VECTORSPACING ; 
 int /*<<< orphan*/  change_c0_intctl (int,int /*<<< orphan*/ ) ; 
 scalar_t__ cpu_has_divec ; 
 scalar_t__ cpu_has_ebase_wg ; 
 scalar_t__ cpu_has_mips_r2_r6 ; 
 scalar_t__ cpu_has_mipsmt ; 
 scalar_t__ cpu_has_veic ; 
 scalar_t__ cpu_has_vint ; 
 unsigned int dvpe () ; 
 int ebase ; 
 int /*<<< orphan*/  evpe (unsigned int) ; 
 int /*<<< orphan*/  set_c0_cause (int /*<<< orphan*/ ) ; 
 unsigned long set_c0_status (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_c0_ebase (int) ; 
 int /*<<< orphan*/  write_c0_ebase_64 (int) ; 
 int /*<<< orphan*/  write_c0_status (unsigned long) ; 

__attribute__((used)) static void configure_exception_vector(void)
{
	if (cpu_has_mips_r2_r6) {
		unsigned long sr = set_c0_status(ST0_BEV);
		/* If available, use WG to set top bits of EBASE */
		if (cpu_has_ebase_wg) {
#ifdef CONFIG_64BIT
			write_c0_ebase_64(ebase | MIPS_EBASE_WG);
#else
			write_c0_ebase(ebase | MIPS_EBASE_WG);
#endif
		}
		write_c0_ebase(ebase);
		write_c0_status(sr);
	}
	if (cpu_has_veic || cpu_has_vint) {
		/* Setting vector spacing enables EI/VI mode  */
		change_c0_intctl(0x3e0, VECTORSPACING);
	}
	if (cpu_has_divec) {
		if (cpu_has_mipsmt) {
			unsigned int vpflags = dvpe();
			set_c0_cause(CAUSEF_IV);
			evpe(vpflags);
		} else
			set_c0_cause(CAUSEF_IV);
	}
}