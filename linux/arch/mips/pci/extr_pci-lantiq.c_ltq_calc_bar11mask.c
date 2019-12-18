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
 int PAGE_SIZE ; 
 int fls (int) ; 
 int get_num_physpages () ; 

__attribute__((used)) static inline u32 ltq_calc_bar11mask(void)
{
	u32 mem, bar11mask;

	/* BAR11MASK value depends on available memory on system. */
	mem = get_num_physpages() * PAGE_SIZE;
	bar11mask = (0x0ffffff0 & ~((1 << (fls(mem) - 1)) - 1)) | 8;

	return bar11mask;
}