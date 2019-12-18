#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  cpic_civr; } ;

/* Variables and functions */
 TYPE_1__* cpic_reg ; 
 int /*<<< orphan*/  cpm_pic_host ; 
 int in_be16 (int /*<<< orphan*/ *) ; 
 int irq_linear_revmap (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  out_be16 (int /*<<< orphan*/ *,int) ; 

int cpm_get_irq(void)
{
	int cpm_vec;

	/*
	 * Get the vector by setting the ACK bit and then reading
	 * the register.
	 */
	out_be16(&cpic_reg->cpic_civr, 1);
	cpm_vec = in_be16(&cpic_reg->cpic_civr);
	cpm_vec >>= 11;

	return irq_linear_revmap(cpm_pic_host, cpm_vec);
}