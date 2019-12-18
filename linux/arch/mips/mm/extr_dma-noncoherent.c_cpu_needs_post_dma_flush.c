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
struct device {int dummy; } ;

/* Variables and functions */
#define  CPU_BMIPS5000 130 
#define  CPU_R10000 129 
#define  CPU_R12000 128 
 int boot_cpu_type () ; 
 int cpu_has_maar ; 

__attribute__((used)) static inline bool cpu_needs_post_dma_flush(struct device *dev)
{
	switch (boot_cpu_type()) {
	case CPU_R10000:
	case CPU_R12000:
	case CPU_BMIPS5000:
		return true;
	default:
		/*
		 * Presence of MAARs suggests that the CPU supports
		 * speculatively prefetching data, and therefore requires
		 * the post-DMA flush/invalidate.
		 */
		return cpu_has_maar;
	}
}