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
typedef  int ib_net64_t ;
typedef  int boolean_t ;

/* Variables and functions */
 int MOD_GIR_COMP_MASK ; 

__attribute__((used)) static inline boolean_t check_mod_comp_mask(ib_net64_t comp_mask)
{
	return ((comp_mask & MOD_GIR_COMP_MASK) == MOD_GIR_COMP_MASK);
}