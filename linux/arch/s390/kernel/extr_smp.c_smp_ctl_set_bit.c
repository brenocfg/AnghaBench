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
struct ec_creg_mask_parms {unsigned long member_0; unsigned long member_1; int member_2; } ;

/* Variables and functions */
 int /*<<< orphan*/  on_each_cpu (int /*<<< orphan*/ ,struct ec_creg_mask_parms*,int) ; 
 int /*<<< orphan*/  smp_ctl_bit_callback ; 

void smp_ctl_set_bit(int cr, int bit)
{
	struct ec_creg_mask_parms parms = { 1UL << bit, -1UL, cr };

	on_each_cpu(smp_ctl_bit_callback, &parms, 1);
}