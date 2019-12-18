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
struct mid_pwr {int dummy; } ;

/* Variables and functions */
 int mid_set_initial_state (struct mid_pwr*,int const*) ; 

__attribute__((used)) static int tng_set_initial_state(struct mid_pwr *pwr)
{
	static const u32 states[] = {
		0xffffffff,		/* PM_SSC(0) */
		0xffffffff,		/* PM_SSC(1) */
		0xffffffff,		/* PM_SSC(2) */
		0xffffffff,		/* PM_SSC(3) */
	};
	return mid_set_initial_state(pwr, states);
}