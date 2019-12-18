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
struct cpuinfo_mips {int cputype; } ;
typedef  enum ftlb_flags { ____Placeholder_ftlb_flags } ftlb_flags ;

/* Variables and functions */
#define  CPU_I6400 133 
#define  CPU_I6500 132 
#define  CPU_LOONGSON3 131 
#define  CPU_P5600 130 
#define  CPU_P6600 129 
#define  CPU_PROAPTIV 128 
 int FTLB_EN ; 
 int FTLB_SET_PROB ; 
 int LOONGSON_DIAG_DTLB ; 
 int LOONGSON_DIAG_FTLB ; 
 int LOONGSON_DIAG_ITLB ; 
 int LOONGSON_DIAG_VTLB ; 
 unsigned int MIPS_CONF6_FTLBDIS ; 
 unsigned int MIPS_CONF6_FTLBEN ; 
 int MIPS_CONF6_FTLBP_SHIFT ; 
 int /*<<< orphan*/  back_to_back_c0_hazard () ; 
 int calculate_ftlb_probability (struct cpuinfo_mips*) ; 
 unsigned int read_c0_config6 () ; 
 int /*<<< orphan*/  write_c0_config6 (unsigned int) ; 
 int /*<<< orphan*/  write_c0_diag (int) ; 

__attribute__((used)) static int set_ftlb_enable(struct cpuinfo_mips *c, enum ftlb_flags flags)
{
	unsigned int config;

	/* It's implementation dependent how the FTLB can be enabled */
	switch (c->cputype) {
	case CPU_PROAPTIV:
	case CPU_P5600:
	case CPU_P6600:
		/* proAptiv & related cores use Config6 to enable the FTLB */
		config = read_c0_config6();

		if (flags & FTLB_EN)
			config |= MIPS_CONF6_FTLBEN;
		else
			config &= ~MIPS_CONF6_FTLBEN;

		if (flags & FTLB_SET_PROB) {
			config &= ~(3 << MIPS_CONF6_FTLBP_SHIFT);
			config |= calculate_ftlb_probability(c)
				  << MIPS_CONF6_FTLBP_SHIFT;
		}

		write_c0_config6(config);
		back_to_back_c0_hazard();
		break;
	case CPU_I6400:
	case CPU_I6500:
		/* There's no way to disable the FTLB */
		if (!(flags & FTLB_EN))
			return 1;
		return 0;
	case CPU_LOONGSON3:
		/* Flush ITLB, DTLB, VTLB and FTLB */
		write_c0_diag(LOONGSON_DIAG_ITLB | LOONGSON_DIAG_DTLB |
			      LOONGSON_DIAG_VTLB | LOONGSON_DIAG_FTLB);
		/* Loongson-3 cores use Config6 to enable the FTLB */
		config = read_c0_config6();
		if (flags & FTLB_EN)
			/* Enable FTLB */
			write_c0_config6(config & ~MIPS_CONF6_FTLBDIS);
		else
			/* Disable FTLB */
			write_c0_config6(config | MIPS_CONF6_FTLBDIS);
		break;
	default:
		return 1;
	}

	return 0;
}