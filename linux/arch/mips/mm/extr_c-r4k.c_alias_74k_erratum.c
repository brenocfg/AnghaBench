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
struct cpuinfo_mips {unsigned int processor_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int MIPS_CONF6_SYND ; 
#define  PRID_IMP_1074K 129 
#define  PRID_IMP_74K 128 
 unsigned int PRID_IMP_MASK ; 
 unsigned int PRID_REV_ENCODE_332 (int,int,int /*<<< orphan*/ ) ; 
 unsigned int PRID_REV_MASK ; 
 int read_c0_config6 () ; 
 int /*<<< orphan*/  write_c0_config6 (int) ; 

__attribute__((used)) static inline int alias_74k_erratum(struct cpuinfo_mips *c)
{
	unsigned int imp = c->processor_id & PRID_IMP_MASK;
	unsigned int rev = c->processor_id & PRID_REV_MASK;
	int present = 0;

	/*
	 * Early versions of the 74K do not update the cache tags on a
	 * vtag miss/ptag hit which can occur in the case of KSEG0/KUSEG
	 * aliases.  In this case it is better to treat the cache as always
	 * having aliases.  Also disable the synonym tag update feature
	 * where available.  In this case no opportunistic tag update will
	 * happen where a load causes a virtual address miss but a physical
	 * address hit during a D-cache look-up.
	 */
	switch (imp) {
	case PRID_IMP_74K:
		if (rev <= PRID_REV_ENCODE_332(2, 4, 0))
			present = 1;
		if (rev == PRID_REV_ENCODE_332(2, 4, 0))
			write_c0_config6(read_c0_config6() | MIPS_CONF6_SYND);
		break;
	case PRID_IMP_1074K:
		if (rev <= PRID_REV_ENCODE_332(1, 1, 0)) {
			present = 1;
			write_c0_config6(read_c0_config6() | MIPS_CONF6_SYND);
		}
		break;
	default:
		BUG();
	}

	return present;
}