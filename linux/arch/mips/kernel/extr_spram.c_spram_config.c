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
#define  CPU_1004K 138 
#define  CPU_1074K 137 
#define  CPU_24K 136 
#define  CPU_34K 135 
#define  CPU_74K 134 
#define  CPU_I6400 133 
#define  CPU_INTERAPTIV 132 
#define  CPU_P5600 131 
#define  CPU_P6600 130 
#define  CPU_PROAPTIV 129 
#define  CPU_QEMU_GENERIC 128 
 int current_cpu_type () ; 
 int /*<<< orphan*/  dspram_load_tag ; 
 int /*<<< orphan*/  dspram_store_tag ; 
 int /*<<< orphan*/  ispram_load_tag ; 
 int /*<<< orphan*/  ispram_store_tag ; 
 int /*<<< orphan*/  probe_spram (char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 unsigned int read_c0_config () ; 

void spram_config(void)
{
	unsigned int config0;

	switch (current_cpu_type()) {
	case CPU_24K:
	case CPU_34K:
	case CPU_74K:
	case CPU_1004K:
	case CPU_1074K:
	case CPU_INTERAPTIV:
	case CPU_PROAPTIV:
	case CPU_P5600:
	case CPU_QEMU_GENERIC:
	case CPU_I6400:
	case CPU_P6600:
		config0 = read_c0_config();
		/* FIXME: addresses are Malta specific */
		if (config0 & (1<<24)) {
			probe_spram("ISPRAM", 0x1c000000,
				    &ispram_load_tag, &ispram_store_tag);
		}
		if (config0 & (1<<23))
			probe_spram("DSPRAM", 0x1c100000,
				    &dspram_load_tag, &dspram_store_tag);
	}
}