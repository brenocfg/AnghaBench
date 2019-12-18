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
struct cpuinfo_mips {int /*<<< orphan*/  gtoffset_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  back_to_back_c0_hazard () ; 
 int /*<<< orphan*/  read_c0_gtoffset () ; 
 int /*<<< orphan*/  write_c0_gtoffset (int) ; 

__attribute__((used)) static inline void cpu_probe_gtoffset(struct cpuinfo_mips *c)
{
	/* determine the number of bits of GTOffset available */
	write_c0_gtoffset(0xffffffff);
	back_to_back_c0_hazard();
	c->gtoffset_mask = read_c0_gtoffset();
	write_c0_gtoffset(0);
}