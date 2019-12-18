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
 scalar_t__ CPU_TX3912 ; 
 int /*<<< orphan*/  blast_dcache16_page (unsigned long) ; 
 scalar_t__ current_cpu_type () ; 

__attribute__((used)) static inline void tx39_blast_dcache_page(unsigned long addr)
{
	if (current_cpu_type() != CPU_TX3912)
		blast_dcache16_page(addr);
}