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

bool arch_kprobe_on_func_entry(unsigned long offset)
{
#ifdef PPC64_ELF_ABI_v2
#ifdef CONFIG_KPROBES_ON_FTRACE
	return offset <= 16;
#else
	return offset <= 8;
#endif
#else
	return !offset;
#endif
}