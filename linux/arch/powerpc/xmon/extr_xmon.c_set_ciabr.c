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
 unsigned long CIABR_PRIV ; 
 unsigned long CIABR_PRIV_HYPER ; 
 unsigned long CIABR_PRIV_SUPER ; 
 int /*<<< orphan*/  CPU_FTR_HVMODE ; 
 scalar_t__ cpu_has_feature (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_ciabr (unsigned long) ; 

__attribute__((used)) static void set_ciabr(unsigned long addr)
{
	addr &= ~CIABR_PRIV;

	if (cpu_has_feature(CPU_FTR_HVMODE))
		addr |= CIABR_PRIV_HYPER;
	else
		addr |= CIABR_PRIV_SUPER;
	write_ciabr(addr);
}